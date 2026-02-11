orte_pre_condition_transports_print(uint64_t *unique_key)
{
    unsigned int *int_ptr;
    size_t i, string_key_len, written_len;
    char *string_key = NULL, *format = NULL;


    string_key_len = (sizeof(uint64_t) * 2) * 2 + strlen("-") + 1;
    string_key = (char*) malloc(string_key_len);
    if (NULL == string_key) {
        return NULL;
    }

    string_key[0] = '\0';
    written_len = 0;


    asprintf(&format, "%%0%dx", (int)(sizeof(unsigned int)) * 2);


    int_ptr = (unsigned int*) &unique_key[0];
    for (i = 0 ; i < sizeof(uint64_t) / sizeof(unsigned int) ; ++i) {
        snprintf(string_key + written_len,
                 string_key_len - written_len,
                 format, int_ptr[i]);
        written_len = strlen(string_key);
    }


    snprintf(string_key + written_len, string_key_len - written_len, "-");
    written_len = strlen(string_key);


    int_ptr = (unsigned int*) &unique_key[1];
    for (i = 0 ; i < sizeof(uint64_t) / sizeof(unsigned int) ; ++i) {
        snprintf(string_key + written_len,
                 string_key_len - written_len,
                 format, int_ptr[i]);
        written_len = strlen(string_key);
    }
    free(format);

    return string_key;
}
