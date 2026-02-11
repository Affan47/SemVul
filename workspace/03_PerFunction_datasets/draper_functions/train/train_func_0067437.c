PyOS_StdioReadline(FILE *sys_stdin, FILE *sys_stdout, const char *prompt)
{
    size_t n;
    char *p, *pr;

    n = 100;
    p = (char *)PyMem_RawMalloc(n);
    if (p == NULL)
        return NULL;

    fflush(sys_stdout);
    if (prompt)
        fprintf(stderr, "%s", prompt);
    fflush(stderr);

    switch (my_fgets(p, (int)n, sys_stdin)) {
    case 0:
        break;
    case 1:
        PyMem_RawFree(p);
        return NULL;
    case -1:
    case -2:
    default:
        *p = '\0';
        break;
    }
    n = strlen(p);
    while (n > 0 && p[n-1] != '\n') {
        size_t incr = n+2;
        if (incr > INT_MAX) {
            PyMem_RawFree(p);
            PyErr_SetString(PyExc_OverflowError, "input line too long");
            return NULL;
        }
        pr = (char *)PyMem_RawRealloc(p, n + incr);
        if (pr == NULL) {
            PyMem_RawFree(p);
            PyErr_NoMemory();
            return NULL;
        }
        p = pr;
        if (my_fgets(p+n, (int)incr, sys_stdin) != 0)
            break;
        n += strlen(p+n);
    }
    pr = (char *)PyMem_RawRealloc(p, n+1);
    if (pr == NULL) {
        PyMem_RawFree(p);
        PyErr_NoMemory();
        return NULL;
    }
    return pr;
}
