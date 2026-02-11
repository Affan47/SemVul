tst_strstr(int line_num, tst_case *tc, const char *haystack,
                   const char *needle)
{
    a_cnt++;
    update_status();
    if (tc->failed && !force) {
        return false;
    }

    if (needle == NULL) {
        return true;
    }
    if (haystack && (strstr(haystack, needle) != NULL)) {
        return true;
    }

    tc->failed = true;
    tst_msg(tc->name, tc->suite->name, line_num,
            "haystack <\"%s\">, doesn't contain needle <\"%s\">\n", haystack, needle);
    return false;
}
