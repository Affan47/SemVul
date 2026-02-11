relational_expr(Program *prog)
{
    opcode_t op;

    if (!additive_expr(prog)) return 0;
    while (1) {
        if (ip[0] == '=') {
	    ip++;
            if      (*ip == '~') op = OP_STREQ;
            else if (*ip == '/') op = OP_MATCH;
            else if (*ip == '=') op = OP_EQUAL;
            else {
                if (pedantic) eprintf("suggestion: use == instead of =");
                op = OP_EQUAL;
		ip--;
            }
        } else if (ip[0] == '!') {
            if      (ip[1] == '~') op = OP_STRNEQ;
            else if (ip[1] == '/') op = OP_NMATCH;
            else if (ip[1] == '=') op = OP_NOTEQ;
            else break;
	    ip++;
        }
        else if (ip[0] == '>') op = (ip[1] == '=') ? ++ip, OP_GTE : *ip;
        else if (ip[0] == '<') op = (ip[1] == '=') ? ++ip, OP_LTE : *ip;
        else break;

        ip++;
        if (!additive_expr(prog)) return 0;
	code_add(prog, op, 2);
    }
    return 1;
}
