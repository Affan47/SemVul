check_unoptimized(const PySTEntryObject* ste) {
    char buf[300];
    const char* trailer;

    if (ste->ste_type != FunctionBlock || !ste->ste_unoptimized
        || !(ste->ste_free || ste->ste_child_free))
        return 1;

    trailer = (ste->ste_child_free ?
                   "contains a nested function with free variables" :
                   "is a nested function");

    switch (ste->ste_unoptimized) {
    case OPT_TOPLEVEL:
    case OPT_EXEC:
        return 1;
    case OPT_IMPORT_STAR:
        PyOS_snprintf(buf, sizeof(buf),
                      "import * is not allowed in function '%.100s' "
                      "because it %s",
                      PyString_AS_STRING(ste->ste_name), trailer);
        break;
    case OPT_BARE_EXEC:
        PyOS_snprintf(buf, sizeof(buf),
                      "unqualified exec is not allowed in function "
                      "'%.100s' it %s",
                      PyString_AS_STRING(ste->ste_name), trailer);
        break;
    default:
        PyOS_snprintf(buf, sizeof(buf),
                      "function '%.100s' uses import * and bare exec, "
                      "which are illegal because it %s",
                      PyString_AS_STRING(ste->ste_name), trailer);
        break;
    }

    PyErr_SetString(PyExc_SyntaxError, buf);
    PyErr_SyntaxLocation(ste->ste_table->st_filename,
                         ste->ste_opt_lineno);
    return 0;
}
