setPassPersist(int action,
               u_char * var_val,
               u_char var_val_type,
               size_t var_val_len,
               u_char * statP, oid * name, size_t name_len)
{
    int             i, rtest;
    struct extensible *persistpassthru;

    char            buf[SNMP_MAXBUF], buf2[SNMP_MAXBUF];
    int             pipe_idx;


    init_persist_pipes();

    for (i = 1; i <= numpersistpassthrus; i++) {
        persistpassthru = get_exten_instance(persistpassthrus, i);
        rtest = snmp_oidtree_compare(name, name_len,
                                     persistpassthru->miboid,
                                     persistpassthru->miblen);
        pipe_idx = i;
#ifdef USING_SINGLE_COMMON_PASSPERSIST_INSTANCE
        pipe_idx =
           get_exten_group_id(persistpassthru->passpersist_inst, i);

        if (pipe_idx != i) {
           persistpassthru = persistpassthru->passpersist_inst;
        }
#endif
        if (rtest <= 0) {
            if (action != ACTION)
                return SNMP_ERR_NOERROR;


            if (persistpassthru->miblen >= name_len || rtest < 0)
                sprint_mib_oid(buf, persistpassthru->miboid,
                               persistpassthru->miblen);
            else
                sprint_mib_oid(buf, name, name_len);
            snprintf(persistpassthru->command,
                     sizeof(persistpassthru->command), "set\n%s\n", buf);
            persistpassthru->command[ sizeof(persistpassthru->command)-1 ] = 0;
            netsnmp_internal_pass_set_format(buf, var_val, var_val_type, var_val_len);
            strlcat(persistpassthru->command, buf,
                    sizeof(persistpassthru->command));
            persistpassthru->command[ sizeof(persistpassthru->command)-2 ] = '\n';
            persistpassthru->command[ sizeof(persistpassthru->command)-1 ] = 0;

            if (!open_persist_pipe(pipe_idx, persistpassthru->name)) {
                return SNMP_ERR_NOTWRITABLE;
            }

            DEBUGMSGTL(("ucd-snmp/pass_persist",
                        "persistpass-writing:  %s\n",
                        persistpassthru->command));
            if (!write_persist_pipe(pipe_idx, persistpassthru->command)) {
                close_persist_pipe(pipe_idx);
                return SNMP_ERR_NOTWRITABLE;
            }

            if (fgets(buf, sizeof(buf), persist_pipes[pipe_idx].fIn) == NULL) {
                close_persist_pipe(pipe_idx);
                return SNMP_ERR_NOTWRITABLE;
            }

            return netsnmp_internal_pass_str_to_errno(buf);
        }
    }
    if (snmp_get_do_debugging()) {
        sprint_mib_oid(buf2, name, name_len);
        DEBUGMSGTL(("ucd-snmp/pass_persist", "persistpass-notfound:  %s\n",
                    buf2));
    }
    return SNMP_ERR_NOSUCHNAME;
}
