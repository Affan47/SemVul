dwarf_harmless_init(struct Dwarf_Harmless_s *dhp,unsigned size)
{
    unsigned i = 0;
    memset(dhp,0,sizeof(*dhp));
    dhp->dh_maxcount = size +1;
    dhp->dh_errors = (char **)malloc(sizeof( char *) *dhp->dh_maxcount);
    if (!dhp->dh_errors) {
        dhp->dh_maxcount = 0;
        return;
    }

    for(i = 0; i < dhp->dh_maxcount; ++i) {
        char *newstr =
            (char *)malloc(DW_HARMLESS_ERROR_MSG_STRING_SIZE);
        dhp->dh_errors[i] = newstr;
        if(!newstr) {
            dhp->dh_maxcount = 0;

            dhp->dh_errors = 0;
            return;
        }


        newstr[0] = 0;
    }
}
