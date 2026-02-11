epr_sub_string(const char* str, int start, int length)
{
    char* str_sub_string = NULL;
    if (str != NULL) {
        str_sub_string = epr_create_string(length);
        strncpy(str_sub_string, str + start, length);
        str_sub_string[length] = '\0';
    }
    return str_sub_string;
}
