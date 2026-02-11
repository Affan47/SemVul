ptql_str_match(sigar_t *sigar, ptql_branch_t *branch, char *value)
{
    if (!branch->value.str) {
        return 0;
    }
#ifndef SIGAR_HAS_PCRE
    if (branch->op_name == PTQL_OP_RE) {
        if (sigar->ptql_re_impl) {
            return sigar->ptql_re_impl(sigar->ptql_re_data,
                                       value,
                                       branch->value.str);
        }
        else {
            return 0;
        }
    }
#endif
    return branch->match.str(branch,
                             value,
                             branch->value.str);
}
