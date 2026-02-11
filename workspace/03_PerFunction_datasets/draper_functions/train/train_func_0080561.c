builtin_compile(PyObject *self, PyObject *args, PyObject *kwds)
{
    char *str;
    PyObject *filename_obj;
    char *filename;
    char *startstr;
    int mode = -1;
    int dont_inherit = 0;
    int supplied_flags = 0;
    int optimize = -1;
    int is_ast;
    PyCompilerFlags cf;
    PyObject *cmd;
    static char *kwlist[] = {"source", "filename", "mode", "flags",
                             "dont_inherit", "optimize", NULL};
    int start[] = {Py_file_input, Py_eval_input, Py_single_input};
    PyObject *result;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "OO&s|iii:compile",  kwlist,
                                     &cmd,
                                     PyUnicode_FSConverter, &filename_obj,
                                     &startstr, &supplied_flags,
                                     &dont_inherit, &optimize))
        return NULL;

    filename = PyBytes_AS_STRING(filename_obj);
    cf.cf_flags = supplied_flags | PyCF_SOURCE_IS_UTF8;

    if (supplied_flags &
        ~(PyCF_MASK | PyCF_MASK_OBSOLETE | PyCF_DONT_IMPLY_DEDENT | PyCF_ONLY_AST))
    {
        PyErr_SetString(PyExc_ValueError,
                        "compile(): unrecognised flags");
        goto error;
    }


    if (optimize < -1 || optimize > 2) {
        PyErr_SetString(PyExc_ValueError,
                        "compile(): invalid optimize value");
        goto error;
    }

    if (!dont_inherit) {
        PyEval_MergeCompilerFlags(&cf);
    }

    if (strcmp(startstr, "exec") == 0)
        mode = 0;
    else if (strcmp(startstr, "eval") == 0)
        mode = 1;
    else if (strcmp(startstr, "single") == 0)
        mode = 2;
    else {
        PyErr_SetString(PyExc_ValueError,
                        "compile() arg 3 must be 'exec', 'eval' or 'single'");
        goto error;
    }

    is_ast = PyAST_Check(cmd);
    if (is_ast == -1)
        goto error;
    if (is_ast) {
        if (supplied_flags & PyCF_ONLY_AST) {
            Py_INCREF(cmd);
            result = cmd;
        }
        else {
            PyArena *arena;
            mod_ty mod;

            arena = PyArena_New();
            mod = PyAST_obj2mod(cmd, arena, mode);
            if (mod == NULL) {
                PyArena_Free(arena);
                goto error;
            }
            if (!PyAST_Validate(mod)) {
                PyArena_Free(arena);
                goto error;
            }
            result = (PyObject*)PyAST_CompileEx(mod, filename,
                                                &cf, optimize, arena);
            PyArena_Free(arena);
        }
        goto finally;
    }

    str = source_as_string(cmd, "compile", "string, bytes, AST or code", &cf);
    if (str == NULL)
        goto error;

    result = Py_CompileStringExFlags(str, filename, start[mode], &cf, optimize);
    goto finally;

error:
    result = NULL;
finally:
    Py_DECREF(filename_obj);
    return result;
}
