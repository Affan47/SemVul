validate_terminal(node *terminal, int type, char *string)
{
    int res = (validate_ntype(terminal, type)
               && ((string == 0) || (strcmp(string, STR(terminal)) == 0)));

    if (!res && !PyErr_Occurred()) {
        PyErr_Format(parser_error,
                     "Illegal terminal: expected \"%s\"", string);
    }
    return (res);
}
