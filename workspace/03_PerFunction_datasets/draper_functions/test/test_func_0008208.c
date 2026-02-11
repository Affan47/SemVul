process_dir(GSList * stack, const gchar * dirname,
                           foreach_file_func func, gint * res)
{
    DIR *dir;
    struct dirent *dir_ent;
    struct stat st;
    gchar *name, *fullname;
    gboolean is_dir = FALSE, is_dir_known;

    dir = opendir(dirname);
    if (dir == NULL) {
        perror(dirname);
        return stack;
    }

    while ((dir_ent = readdir(dir)) != NULL) {
        name = dir_ent->d_name;

        if (name[0] == '.' &&
            (name[1] == '\0' || (name[1] == '.' && name[2] == '\0')))

            continue;

        fullname = g_build_filename(dirname, name, NULL);
        is_dir_known = FALSE;

#ifdef _DIRENT_HAVE_D_TYPE
        switch (dir_ent->d_type) {
        case DT_UNKNOWN:
        case DT_LNK:
            break;

        case DT_DIR:
            is_dir = TRUE;
            is_dir_known = TRUE;
            break;

        default:
            is_dir = FALSE;
            is_dir_known = TRUE;
            break;
        }
#endif

        if (is_dir_known == FALSE && !stat(fullname, &st)) {
            is_dir = S_ISDIR(st.st_mode);
            is_dir_known = TRUE;
        }

        if (is_dir_known) {
            if (is_dir)

                stack = g_slist_prepend(stack, fullname);
            else {

                *res += (*func) (fullname);
                g_free(fullname);
            }
        }
    }

    closedir(dir);
    return stack;
}
