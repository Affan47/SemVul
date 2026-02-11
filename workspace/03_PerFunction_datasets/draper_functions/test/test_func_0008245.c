write_translated_name(char *new_name, char *old_name,
                                 char *prefix_path, int start_pos,
                                 char *extension)
{   int x;
    if (strlen(old_name)+strlen(extension) >= PATHLEN) {
        printf("One of your filenames is longer than %d characters.\n", PATHLEN);
        exit(1);
    }
    if (prefix_path == NULL)
    {   sprintf(new_name,"%s%s", old_name, extension);
        return 0;
    }
    strcpy(new_name, prefix_path + start_pos);
    for (x=0; (new_name[x]!=0) && (new_name[x]!=FN_ALT); x++) ;
    if (new_name[x] == 0) start_pos = 0; else start_pos += x+1;
    if (x+strlen(old_name)+strlen(extension) >= PATHLEN) {
        printf("One of your pathnames is longer than %d characters.\n", PATHLEN);
        exit(1);
    }
    sprintf(new_name + x, "%s%s", old_name, extension);
    return start_pos;
}
