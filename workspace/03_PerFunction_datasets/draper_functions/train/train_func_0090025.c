make_string(char **no_newline_string, output_desc_t *ldi,
                       const char *format, va_list arglist)
{
    size_t len, total_len;
    bool want_newline = false;


    vasprintf(no_newline_string, format, arglist);
    total_len = len = strlen(*no_newline_string);
    if ('\n' != (*no_newline_string)[len - 1]) {
        want_newline = true;
        ++total_len;
    } else if (NULL != ldi->ldi_suffix) {


        (*no_newline_string)[len - 1] = '\0';
        want_newline = true;


    }
    if (NULL != ldi->ldi_prefix) {
        total_len += strlen(ldi->ldi_prefix);
    }
    if (NULL != ldi->ldi_suffix) {
        total_len += strlen(ldi->ldi_suffix);
    }
    if (temp_str_len < total_len + want_newline) {
        if (NULL != temp_str) {
            free(temp_str);
        }
        temp_str = (char *) malloc(total_len * 2);
        if (NULL == temp_str) {
            return OPAL_ERR_OUT_OF_RESOURCE;
        }
        temp_str_len = total_len * 2;
    }
    if (NULL != ldi->ldi_prefix && NULL != ldi->ldi_suffix) {
        if (want_newline) {
            snprintf(temp_str, temp_str_len, "%s%s%s\n",
                     ldi->ldi_prefix, *no_newline_string, ldi->ldi_suffix);
        } else {
            snprintf(temp_str, temp_str_len, "%s%s%s", ldi->ldi_prefix,
                     *no_newline_string, ldi->ldi_suffix);
        }
    } else if (NULL != ldi->ldi_prefix) {
        if (want_newline) {
            snprintf(temp_str, temp_str_len, "%s%s\n",
                     ldi->ldi_prefix, *no_newline_string);
        } else {
            snprintf(temp_str, temp_str_len, "%s%s", ldi->ldi_prefix,
                     *no_newline_string);
        }
    } else if (NULL != ldi->ldi_suffix) {
        if (want_newline) {
            snprintf(temp_str, temp_str_len, "%s%s\n",
                     *no_newline_string, ldi->ldi_suffix);
        } else {
            snprintf(temp_str, temp_str_len, "%s%s",
                     *no_newline_string, ldi->ldi_suffix);
        }
    } else {
        if (want_newline) {
            snprintf(temp_str, temp_str_len, "%s\n", *no_newline_string);
        } else {
            snprintf(temp_str, temp_str_len, "%s", *no_newline_string);
        }
    }

    return OPAL_SUCCESS;
}
