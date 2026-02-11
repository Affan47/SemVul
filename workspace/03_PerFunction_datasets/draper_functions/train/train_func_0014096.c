awt_get_selected_fullname(AW_root *awr, const char *awar_prefix) {
    char *file = awr->awar(GBS_global_string("%s/file_name", awar_prefix))->read_string();
    if (file[0] != '/') {


        char    *awar_dir_name = GBS_global_string_copy("%s/directory", awar_prefix);
        AW_awar *awar_dir      = awr->awar_no_error(awar_dir_name);

        if (!awar_dir) {

            awar_dir = awr->awar_string(awar_dir_name, GB_getcwd());
        }

        awt_assert(awar_dir);

        char *dir = awar_dir->read_string();
        if (!dir[0]) {
            awar_dir->write_string(GB_getcwd());
            freeset(dir, awar_dir->read_string());
        }

        char *full = strdup(GB_concat_full_path(dir, file));

        free(dir);
        free(file);

        file = full;

        free(awar_dir_name);
    }

    return file;
}
