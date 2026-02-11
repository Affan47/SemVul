gdnsd_linux_min_version(const unsigned x, const unsigned y, const unsigned z) {
    bool rv = false;
    struct utsname uts;
    if(!uname(&uts) && !strcmp("Linux", uts.sysname)) {
        unsigned sys_x, sys_y, sys_z;
        if(sscanf(uts.release, "%u.%u.%u", &sys_x, &sys_y, &sys_z) == 3) {
            const uint32_t vers_have = _version_fold(sys_x, sys_y, sys_z);
            const uint32_t vers_wanted = _version_fold(x, y, z);
            if(vers_have >= vers_wanted)
                rv = true;
        }
    }
    return rv;
}
