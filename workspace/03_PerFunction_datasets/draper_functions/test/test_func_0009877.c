x509_crl_info( char *buf, size_t size, const char *prefix,
                   const x509_crl *crl )
{
    int ret;
    size_t n;
    char *p;
    const char *desc;
    const x509_crl_entry *entry;

    p = buf;
    n = size;

    ret = snprintf( p, n, "%sCRL version   : %d",
                               prefix, crl->version );
    SAFE_SNPRINTF();

    ret = snprintf( p, n, "\n%sissuer name   : ", prefix );
    SAFE_SNPRINTF();
    ret = x509_dn_gets( p, n, &crl->issuer );
    SAFE_SNPRINTF();

    ret = snprintf( p, n, "\n%sthis update   : " \
                   "%04d-%02d-%02d %02d:%02d:%02d", prefix,
                   crl->this_update.year, crl->this_update.mon,
                   crl->this_update.day,  crl->this_update.hour,
                   crl->this_update.min,  crl->this_update.sec );
    SAFE_SNPRINTF();

    ret = snprintf( p, n, "\n%snext update   : " \
                   "%04d-%02d-%02d %02d:%02d:%02d", prefix,
                   crl->next_update.year, crl->next_update.mon,
                   crl->next_update.day,  crl->next_update.hour,
                   crl->next_update.min,  crl->next_update.sec );
    SAFE_SNPRINTF();

    entry = &crl->entry;

    ret = snprintf( p, n, "\n%sRevoked certificates:",
                               prefix );
    SAFE_SNPRINTF();

    while( entry != NULL && entry->raw.len != 0 )
    {
        ret = snprintf( p, n, "\n%sserial number: ",
                               prefix );
        SAFE_SNPRINTF();

        ret = x509_serial_gets( p, n, &entry->serial);
        SAFE_SNPRINTF();

        ret = snprintf( p, n, " revocation date: " \
                   "%04d-%02d-%02d %02d:%02d:%02d",
                   entry->revocation_date.year, entry->revocation_date.mon,
                   entry->revocation_date.day,  entry->revocation_date.hour,
                   entry->revocation_date.min,  entry->revocation_date.sec );
        SAFE_SNPRINTF();

        entry = entry->next;
    }

    ret = snprintf( p, n, "\n%ssigned using  : ", prefix );
    SAFE_SNPRINTF();

    ret = oid_get_sig_alg_desc( &crl->sig_oid1, &desc );
    if( ret != 0 )
        ret = snprintf( p, n, "???"  );
    else
        ret = snprintf( p, n, "%s", desc );
    SAFE_SNPRINTF();

    ret = snprintf( p, n, "\n" );
    SAFE_SNPRINTF();

    return( (int) ( size - n ) );
}
