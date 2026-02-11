mount3udp_delete_mountlist (char *hostname, dirpath *expname)
{
        struct mount3_state     *ms = NULL;
        char                    *export = NULL;

        ms = mnt3prog.private;
        export = (char *)expname;
        while (*export == '/')
                export++;
        __mnt3svc_umount (ms, export, hostname);
        return 0;
}
