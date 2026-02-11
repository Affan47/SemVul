netsnmp_get_pid_from_inode_init(void)
{
    DIR            *procdirs = NULL, *piddirs = NULL;
    char            path_name[PATH_MAX + 1];
    char            socket_lnk[NAME_MAX + 1];
    int             filelen = 0, readlen = 0;
    struct dirent  *procinfo, *pidinfo;
    pid_t           pid = 0;
    ino64_t         temp_inode;

    _clear();


    if (!(procdirs = opendir(PROC_PATH))) {
        NETSNMP_LOGONCE((LOG_ERR, "snmpd: cannot open /proc\n"));
        return;
    }

    while ((procinfo = readdir(procdirs)) != NULL) {
        const char* name = procinfo->d_name;


        for (; *name; name++) {
            if (!isdigit(*name))
                break;
        }
        if(*name)
            continue;


        memset(path_name, '\0', PATH_MAX + 1);
        filelen = snprintf(path_name, PATH_MAX,
                           PROC_PATH "/%s/fd/", procinfo->d_name);
        if (filelen <= 0 || PATH_MAX < filelen)
            continue;


        if (!(piddirs = opendir(path_name)))
        continue;

        while ((pidinfo = readdir(piddirs)) != NULL) {
            if (filelen + strlen(pidinfo->d_name) > PATH_MAX)
                continue;

            strcpy(path_name + filelen, pidinfo->d_name);


            memset(socket_lnk, '\0', NAME_MAX + 1);
            readlen = readlink(path_name, socket_lnk, NAME_MAX);
            if (readlen < 0)
                continue;

            socket_lnk[readlen] = '\0';


            if (!strncmp(socket_lnk, SOCKET_TYPE_1, 8)) {
                temp_inode = strtoull(socket_lnk + 8, NULL, 0);
            } else if (!strncmp(socket_lnk, SOCKET_TYPE_2, 7)) {
                temp_inode = strtoull(socket_lnk + 7, NULL, 0);
            } else {
                temp_inode = 0;
            }


            if (temp_inode != 0) {
                pid = strtoul(procinfo->d_name, NULL, 0);
                _set(temp_inode, pid);
            }
        }
        closedir(piddirs);
    }
    if (procdirs)
        closedir(procdirs);
}
