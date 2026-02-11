update_princ_encryption_1(void *cb, krb5_db_entry *ent)
{
    struct update_enc_mkvno *p = cb;
    char *pname = 0;
    krb5_error_code retval;
    int match;
    krb5_timestamp now;
    int result;
    krb5_kvno old_mkvno;

    retval = krb5_unparse_name(util_context, ent->princ, &pname);
    if (retval) {
        com_err(progname, retval,
                _("getting string representation of principal name"));
        goto fail;
    }

    if (krb5_principal_compare(util_context, ent->princ, master_princ)) {
        goto skip;
    }

#ifdef SOLARIS_REGEXPS
    match = (step(pname, p->expbuf) != 0);
#endif
#ifdef POSIX_REGEXPS
    match = (regexec(&p->preg, pname, 0, NULL, 0) == 0);
#endif
#ifdef BSD_REGEXPS
    match = (re_exec(pname) != 0);
#endif
    if (!match) {
        goto skip;
    }
    p->re_match_count++;
    retval = krb5_dbe_get_mkvno(util_context, ent, &old_mkvno);
    if (retval) {
        com_err(progname, retval,
                _("determining master key used for principal '%s'"), pname);
        goto fail;
    }

    if (old_mkvno == new_mkvno) {
        if (p->dry_run && p->verbose)
            printf(_("would skip:   %s\n"), pname);
        else if (p->verbose)
            printf(_("skipping: %s\n"), pname);
        p->already_current++;
        goto skip;
    }
    if (p->dry_run) {
        if (p->verbose)
            printf(_("would update: %s\n"), pname);
        p->updated++;
        goto skip;
    } else if (p->verbose)
        printf(_("updating: %s\n"), pname);
    retval = master_key_convert (util_context, ent);
    if (retval) {
        com_err(progname, retval,
                _("error re-encrypting key for principal '%s'"), pname);
        goto fail;
    }
    if ((retval = krb5_timeofday(util_context, &now))) {
        com_err(progname, retval, _("while getting current time"));
        goto fail;
    }

    if ((retval = krb5_dbe_update_mod_princ_data(util_context, ent,
                                                 now, master_princ))) {
        com_err(progname, retval,
                _("while updating principal '%s' modification time"), pname);
        goto fail;
    }

    ent->mask |= KADM5_KEY_DATA;

    if ((retval = krb5_db_put_principal(util_context, ent))) {
        com_err(progname, retval, _("while updating principal '%s' key data "
                                    "in the database"), pname);
        goto fail;
    }
    p->updated++;
skip:
    result = 0;
    goto egress;
fail:
    exit_status++;
    result = 1;
egress:
    if (pname)
        krb5_free_unparsed_name(util_context, pname);
    return result;
}
