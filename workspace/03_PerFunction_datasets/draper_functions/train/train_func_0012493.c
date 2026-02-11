_dump_v6stats( const char *name, oid *oid_buf, size_t buf_len,
               struct stat_table *stable )
{
    netsnmp_variable_list *var, *vp;
    struct stat_table     *sp;
    oid   *stats, stat;
    unsigned int max_stat = 0;
    int    active   = 0;

    var = NULL;
    for (sp=stable; sp->entry; sp++) {
        oid_buf[buf_len-1] = sp->entry;
        if (sp->entry>max_stat)
            max_stat = sp->entry;
        snmp_varlist_add_variable( &var, oid_buf, buf_len,
                                   ASN_NULL, NULL,  0);
    }
    oid_buf[buf_len-1] = stable[0].entry;
    stats = (oid *)calloc(max_stat+1, sizeof(oid));


    while (1) {
        if (netsnmp_query_getnext( var, ss ) != SNMP_ERR_NOERROR)
            break;
        if ( snmp_oid_compare( oid_buf,   buf_len-1,
                               var->name, buf_len-1) != 0 )
            break;

        for ( vp=var; vp; vp=vp->next_variable ) {
            stat = var->name[ buf_len-1 ];
            stats[stat] += *vp->val.integer;
        }
        active=1;
    }
    if (!active) {
        free( stats );
        snmp_free_varbind( var );
        return;
    }


    printf("%s:\n", name);
    for (sp=stable; sp->entry; sp++) {


        if ( stats[sp->entry] > 0 || sflag == 1 ) {
            putchar('\t');
            printf(sp->description, stats[sp->entry],
                             plural(stats[sp->entry]));
            putchar('\n');
        }
    }
    free( stats );
    snmp_free_varbind( var );
}
