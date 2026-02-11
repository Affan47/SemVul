assemble_init(struct assembler *a, int nblocks, int firstlineno)
{
    memset(a, 0, sizeof(struct assembler));
    a->a_lineno = firstlineno;
    a->a_bytecode = PyBytes_FromStringAndSize(NULL, DEFAULT_CODE_SIZE);
    if (!a->a_bytecode)
        return 0;
    a->a_lnotab = PyBytes_FromStringAndSize(NULL, DEFAULT_LNOTAB_SIZE);
    if (!a->a_lnotab)
        return 0;
    if ((size_t)nblocks > PY_SIZE_MAX / sizeof(basicblock *)) {
        PyErr_NoMemory();
        return 0;
    }
    a->a_postorder = (basicblock **)PyObject_Malloc(
                                        sizeof(basicblock *) * nblocks);
    if (!a->a_postorder) {
        PyErr_NoMemory();
        return 0;
    }
    return 1;
}
