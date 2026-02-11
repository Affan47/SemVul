netsnmp_gethostbyname(const char *name)
{
#if HAVE_GETHOSTBYNAME
#ifdef DNSSEC_LOCAL_VALIDATION
    val_status_t val_status;
#endif
    struct hostent *hp = NULL;

    if (NULL == name)
        return NULL;

    DEBUGMSGTL(("dns:gethostbyname", "looking up %s\n", name));

#ifdef DNSSEC_LOCAL_VALIDATION
    hp  = val_gethostbyname(netsnmp_validator_context(), name, &val_status);
    DEBUGMSGTL(("dns:sec:val", "val_status %d / %s; trusted: %d\n",
                val_status, p_val_status(val_status),
                val_istrusted(val_status)));
    if (!val_istrusted(val_status)) {
        snmp_log(LOG_WARNING,
                 "The authenticity of DNS response is not trusted (%s)\n",
                 p_val_status(val_status));

        if (!netsnmp_ds_get_boolean(NETSNMP_DS_LIBRARY_ID,
                                    NETSNMP_DS_LIB_DNSSEC_WARN_ONLY))
            hp = NULL;
    }
    else if (val_does_not_exist(val_status) && hp)
        hp = NULL;
#else
    hp = gethostbyname(name);
#endif
    if (hp == NULL) {
        DEBUGMSGTL(("dns:gethostbyname",
                    "couldn't resolve %s\n", name));
    } else if (hp->h_addrtype != AF_INET) {
        DEBUGMSGTL(("dns:gethostbyname",
                    "warning: response for %s not AF_INET!\n", name));
    } else {
        DEBUGMSGTL(("dns:gethostbyname",
                    "%s resolved okay\n", name));
    }
    return hp;
#else
    NETSNMP_LOGONCE((LOG_ERR, "gethostbyname not available"));
    return NULL;
#endif
}
