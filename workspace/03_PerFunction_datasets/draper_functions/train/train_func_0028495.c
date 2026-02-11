blogc_get_filename(const char *f)
{
    if (f == NULL)
        return NULL;

    if (strlen(f) == 0)
        return NULL;

    char *filename = sb_strdup(f);


    char *tmp = filename;

    bool removed_dot = false;
    for (int i = strlen(tmp); i >= 0 ; i--) {


        if (!removed_dot && tmp[i] == '.') {
            tmp[i] = '\0';
            removed_dot = true;
            continue;
        }

        if (tmp[i] == '/' || tmp[i] == '\\') {
            tmp += i + 1;
            break;
        }
    }

    char *final_filename = sb_strdup(tmp);
    free(filename);

    return final_filename;
}
