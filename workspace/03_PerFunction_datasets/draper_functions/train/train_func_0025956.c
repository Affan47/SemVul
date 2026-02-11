ptql_op_str_sw(ptql_branch_t *branch,
                          char *haystack, char *needle)
{
    return branch_strnEQ(branch, haystack, needle, strlen(needle));
}
