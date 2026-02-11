lookupOperator(const char *opname)
{
    int opid;
    int negate = 1;
    if (opname[0] == '!') {
        negate = -1;
        opname ++;
    }

    if (!strcmp(opname, "="))
        opid = OP_EQUAL;
    else if (!strcmp(opname, "~"))
        opid = OP_REGEX;
    else if (!strcmp(opname, "=~"))
        opid = OP_EQUAL_ICASE;
    else if (!strcmp(opname, "~~"))
        opid = OP_REGEX_ICASE;
    else if (!strcmp(opname, ">"))
        opid = OP_GREATER;
    else if (!strcmp(opname, "<"))
        opid = OP_LESS;
    else if (!strcmp(opname, ">=")) {
        opid = OP_LESS;
        negate = -negate;
    }
    else if (!strcmp(opname, "<=")) {
        opid = OP_GREATER;
        negate = -negate;
    }
    else
        opid = OP_INVALID;
    return negate * opid;
}
