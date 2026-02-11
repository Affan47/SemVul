netsnmp_str_to_gid(const char *grouporgid) {
    int gid;
#if HAVE_GETGRNAM && HAVE_GRP_H
    struct group  *grp;
#endif

    gid = atoi(grouporgid);

    if ( gid == 0 ) {
#if HAVE_GETGRNAM && HAVE_GRP_H
        grp = getgrnam( grouporgid );
        if (grp)
            gid = grp->gr_gid;
        else
#endif
            snmp_log(LOG_WARNING, "Can't identify group (%s).\n",
                     grouporgid);
    }

    return gid;
}
