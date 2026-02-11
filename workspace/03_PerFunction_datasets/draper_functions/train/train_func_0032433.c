parse_opargtext(
    var_t *var, var_parse_t *ctx,
    const char *begin, const char *end)
{
    const char *p;


    for (p = begin; p != end && *p != var->syntax.delim_init && *p != ')'; p++) {
        if (*p == var->syntax.escape) {
            if (p + 1 == end)
                return VAR_ERR_INCOMPLETE_QUOTED_PAIR;
            p++;
        }
    }
    return (p - begin);
}
