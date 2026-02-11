profile_init_path(const_profile_filespec_list_t filepath,
                  profile_t *ret_profile)
{
    unsigned int n_entries;
    int i;
    unsigned int ent_len;
    const char *s, *t;
    profile_filespec_t *filenames;
    errcode_t retval;


    for(s = filepath, n_entries = 1; *s; s++) {
        if (*s == ':')
            n_entries++;
    }


    filenames = (profile_filespec_t*) malloc((n_entries+1) * sizeof(char*));
    if (filenames == 0)
        return ENOMEM;


    for(s = filepath, i=0; (t = strchr(s, ':')) || (t=s+strlen(s)); s=t+1, i++) {
        ent_len = (unsigned int) (t-s);
        filenames[i] = (char*) malloc(ent_len + 1);
        if (filenames[i] == 0) {

            while(--i >= 0) free(filenames[i]);
            free(filenames);
            return ENOMEM;
        }
        strncpy(filenames[i], s, ent_len);
        filenames[i][ent_len] = 0;
        if (*t == 0) {
            i++;
            break;
        }
    }

    filenames[i] = 0;

    retval = profile_init_flags((const_profile_filespec_t *) filenames, 0,
                                ret_profile);


    while(--i >= 0) free(filenames[i]);
    free(filenames);

    return retval;
}
