snmp_parse_oid(const char *argv, oid * root, size_t * rootlen)
{
    size_t          savlen = *rootlen;
    static size_t   tmpbuf_len = 0;
    static char    *tmpbuf;
    const char     *suffix, *prefix;

    suffix = netsnmp_ds_get_string(NETSNMP_DS_LIBRARY_ID,
                                   NETSNMP_DS_LIB_OIDSUFFIX);
    prefix = netsnmp_ds_get_string(NETSNMP_DS_LIBRARY_ID,
                                   NETSNMP_DS_LIB_OIDPREFIX);
    if ((suffix && suffix[0]) || (prefix && prefix[0])) {
        if (!suffix)
            suffix = "";
        if (!prefix)
            prefix = "";
        if ((strlen(suffix) + strlen(prefix) + strlen(argv) + 2) > tmpbuf_len) {
            tmpbuf_len = strlen(suffix) + strlen(argv) + strlen(prefix) + 2;
            tmpbuf = (char *)realloc(tmpbuf, tmpbuf_len);
        }
        snprintf(tmpbuf, tmpbuf_len, "%s%s%s%s", prefix, argv,
                 ((suffix[0] == '.' || suffix[0] == '\0') ? "" : "."),
                 suffix);
        argv = tmpbuf;
        DEBUGMSGTL(("snmp_parse_oid","Parsing: %s\n",argv));
    }

#ifndef NETSNMP_DISABLE_MIB_LOADING
    if (netsnmp_ds_get_boolean(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_RANDOM_ACCESS)
        || strchr(argv, ':')) {
        if (get_node(argv, root, rootlen)) {
            return root;
        }
    } else if (netsnmp_ds_get_boolean(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_REGEX_ACCESS)) {
	clear_tree_flags(tree_head);
        if (get_wild_node(argv, root, rootlen)) {
            return root;
        }
    } else {
#endif
        if (read_objid(argv, root, rootlen)) {
            return root;
        }
#ifndef NETSNMP_DISABLE_MIB_LOADING
        *rootlen = savlen;
        if (get_node(argv, root, rootlen)) {
            return root;
        }
        *rootlen = savlen;
        DEBUGMSGTL(("parse_oid", "wildly parsing\n"));
	clear_tree_flags(tree_head);
        if (get_wild_node(argv, root, rootlen)) {
            return root;
        }
    }
#endif
    return NULL;
}
