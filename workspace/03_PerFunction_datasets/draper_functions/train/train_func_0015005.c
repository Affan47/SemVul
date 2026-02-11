crm_parse_int(const char *text, const char *default_text)
{
    int atoi_result = -1;

    if (text != NULL) {
        atoi_result = crm_int_helper(text, NULL);
        if (errno == 0) {
            return atoi_result;
        }
    }

    if (default_text != NULL) {
        atoi_result = crm_int_helper(default_text, NULL);
        if (errno == 0) {
            return atoi_result;
        }

    } else {
        crm_err("No default conversion value supplied");
    }

    return -1;
}
