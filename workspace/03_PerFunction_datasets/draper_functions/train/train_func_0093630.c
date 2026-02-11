ompi_info_get_bool(ompi_info_t *info, char *key, bool *value, int *flag)
{
    char *ptr;
    char str[256];

    str[sizeof(str) - 1] = '\0';
    ompi_info_get(info, key, sizeof(str) - 1, str, flag);
    if (*flag) {
        *value = false;


        ptr = str + sizeof(str) - 1;
        while (ptr >= str && isspace(*ptr)) {
            *ptr = '\0';
            --ptr;
        }
        ptr = str;
        while (ptr < str + sizeof(str) - 1 && *ptr != '\0' &&
               isspace(*ptr)) {
            ++ptr;
        }
        if ('\0' != *ptr) {
            if (isdigit(*ptr)) {
                *value = (bool) atoi(ptr);
            } else if (0 == strcasecmp(ptr, "yes") ||
                       0 == strcasecmp(ptr, "true")) {
                *value = true;
            } else if (0 != strcasecmp(ptr, "no") &&
                       0 != strcasecmp(ptr, "false")) {

            }
        }
    }
    return MPI_SUCCESS;
}
