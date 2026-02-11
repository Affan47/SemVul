se_read_conf(const char *word, char *cptr)
{
    int major, minor;
    int value;
    char *cp, *cp2;
    char e_name[BUFSIZ];
    char e_enum[  BUFSIZ];

    if (!cptr || *cptr=='\0')
        return;


    cp = copy_nword(cptr, e_name, sizeof(e_name));
    cp = skip_white(cp);
    if (!cp || *cp=='\0')
        return;


    if (sscanf(e_name, "%d:%d", &major, &minor) == 2) {


        while (1) {
            cp = copy_nword(cp, e_enum, sizeof(e_enum));
            if (sscanf(e_enum, "%d:", &value) != 1) {
                break;
            }
            cp2 = e_enum;
            while (*(cp2++) != ':')
                ;
            se_add_pair(major, minor, strdup(cp2), value);
            if (!cp)
                break;
        }
    } else {


        while (1) {
            cp = copy_nword(cp, e_enum, sizeof(e_enum));
            if (sscanf(e_enum, "%d:", &value) != 1) {
                break;
            }
            cp2 = e_enum;
            while (*(cp2++) != ':')
                ;
            se_add_pair_to_slist(e_name, strdup(cp2), value);
            if (!cp)
                break;
        }
    }
}
