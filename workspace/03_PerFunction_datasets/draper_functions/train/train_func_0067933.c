open(const char *path) {
    if (AD_fast == MAXCACH) {
        gbd = GB_open(path,"rw");
    } else {
        gbd = GB_open(path,"rwt");
    }
    if (gbd) {
        GB_begin_transaction(gbd);

        species_data = GB_entry(gbd,"species_data");
        sai_data     = GB_entry(gbd,"extended_data");
        presets      = GB_entry(gbd,"presets");

        GB_commit_transaction(gbd);

        gbdataptr = gbd;
        return 0;
    } else
    {
        return new AD_ERR("database doesn't exist");
    }
}
