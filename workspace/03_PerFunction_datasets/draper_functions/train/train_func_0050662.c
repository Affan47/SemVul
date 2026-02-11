sort_field_auto_evaluate(SortField *sf, char *text)
{
    int int_val;
    float float_val;
    int text_len = 0, scan_len = 0;

    text_len = (int)strlen(text);
    sscanf(text, "%d%n", &int_val, &scan_len);
    if (scan_len == text_len) {
        sort_field_int_methods(sf);
    } else {
        sscanf(text, "%f%n", &float_val, &scan_len);
        if (scan_len == text_len) {
            sort_field_float_methods(sf);
        } else {
            sort_field_string_methods(sf);
        }
    }
}
