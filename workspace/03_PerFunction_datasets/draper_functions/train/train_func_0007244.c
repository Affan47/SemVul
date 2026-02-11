exprsub(Program *prog, int in_expr)
{
    int result = 0;

    ip++;
    eat_space(prog);
    if (!expr(prog)) return 0;
    if (!*ip || is_end_of_statement(ip)) {
        eprintf("unmatched $[");
    } else if (*ip != ']') {
        parse_error(prog, "expression", "operator or ']'");
    } else {
	if (!in_expr)
	    code_add(prog, OP_APPEND, NULL);
        ++ip;
        result = 1;
    }
    return result;
}
