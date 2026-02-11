regex_parse_node_ranges(char *base, char *ranges, int num_digits, char *suffix, char ***names)
{
    int i, len, ret;
    char *start, *orig;


    len = strlen(ranges);
    for (orig = start = ranges, i = 0; i < len; ++i) {
        if (',' == ranges[i]) {
            ranges[i] = '\0';
            ret = regex_parse_node_range(base, start, num_digits, suffix, names);
            if (ORTE_SUCCESS != ret) {
                ORTE_ERROR_LOG(ret);
                return ret;
            }
            start = ranges + i + 1;
        }
    }


    if (start < orig + len) {

        OPAL_OUTPUT_VERBOSE((1, orte_debug_output,
                             "%s regex:parse:ranges: parse range %s (2)",
                             ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), start));

        ret = regex_parse_node_range(base, start, num_digits, suffix, names);
        if (ORTE_SUCCESS != ret) {
            ORTE_ERROR_LOG(ret);
            return ret;
        }
    }


    return ORTE_SUCCESS;
}
