PyRun_StringFlags(const char *str, int start, PyObject *globals,
                  PyObject *locals, PyCompilerFlags *flags)
{
    PyObject *ret = NULL;
    mod_ty mod;
    PyArena *arena = PyArena_New();
    if (arena == NULL)
        return NULL;

    mod = PyParser_ASTFromString(str, "<string>", start, flags, arena);
    if (mod != NULL)
        ret = run_mod(mod, "<string>", globals, locals, flags, arena);
    PyArena_Free(arena);
    return ret;
}
