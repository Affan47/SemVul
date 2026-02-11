writestring(char *feld,char *eintrag) {
    GBDATA *gbptr = 0;
    GB_TYPES type;
    GB_ERROR error;
    if (gbdataptr != 0) {
        gbptr = GB_entry(gbdataptr,feld);
    }
    if (gbptr != 0) {
        type = GB_read_type(gbptr);
        if (type == GB_STRING ) {
            error = GB_write_string(gbptr,eintrag);
            if (error == 0) {
                return 0; }
            return new AD_ERR("writestring not possible");
        }
        return new AD_ERR("writestring on non string entry!");
    }
    return new AD_ERR("writestring: feld not existing",CORE);
}
