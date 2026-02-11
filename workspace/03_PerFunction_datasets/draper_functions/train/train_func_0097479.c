add_admin_princs(void *handle, krb5_context context, char *realm)
{
    krb5_error_code ret = 0;
    char *service_name = 0, *p;
    char localname[MAXHOSTNAMELEN];
    struct addrinfo *ai, ai_hints;
    int gai_error;

    if (gethostname(localname, MAXHOSTNAMELEN)) {
        ret = errno;
        perror("gethostname");
        goto clean_and_exit;
    }
    memset(&ai_hints, 0, sizeof(ai_hints));
    ai_hints.ai_flags = AI_CANONNAME | AI_ADDRCONFIG;
    gai_error = getaddrinfo(localname, (char *)NULL, &ai_hints, &ai);
    if (gai_error) {
        ret = EINVAL;
        fprintf(stderr, "getaddrinfo(%s): %s\n", localname,
                gai_strerror(gai_error));
        goto clean_and_exit;
    }
    if (ai->ai_canonname == NULL) {
        ret = EINVAL;
        fprintf(stderr, _("getaddrinfo(%s): Cannot determine canonical "
                          "hostname.\n"), localname);
        freeaddrinfo(ai);
        goto clean_and_exit;
    }
    for (p = ai->ai_canonname; *p; p++) {
#ifdef isascii
        if (!isascii(*p))
            continue;
#else
        if (*p < ' ')
            continue;
        if (*p > '~')
            continue;
#endif
        if (!isupper(*p))
            continue;
        *p = tolower(*p);
    }
    if (asprintf(&service_name, "kadmin/%s", ai->ai_canonname) < 0) {
        ret = ENOMEM;
        fprintf(stderr, _("Out of memory\n"));
        freeaddrinfo(ai);
        goto clean_and_exit;
    }
    freeaddrinfo(ai);

    if ((ret = add_admin_princ(handle, context,
                               service_name, realm,
                               KRB5_KDB_DISALLOW_TGT_BASED,
                               ADMIN_LIFETIME)))
        goto clean_and_exit;

    if ((ret = add_admin_princ(handle, context,
                               KADM5_ADMIN_SERVICE, realm,
                               KRB5_KDB_DISALLOW_TGT_BASED,
                               ADMIN_LIFETIME)))
        goto clean_and_exit;

    if ((ret = add_admin_princ(handle, context,
                               KADM5_CHANGEPW_SERVICE, realm,
                               KRB5_KDB_DISALLOW_TGT_BASED |
                               KRB5_KDB_PWCHANGE_SERVICE,
                               CHANGEPW_LIFETIME)))
        goto clean_and_exit;

clean_and_exit:
    free(service_name);

    return ret;
}
