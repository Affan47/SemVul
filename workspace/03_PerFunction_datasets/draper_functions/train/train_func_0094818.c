PyFloat_Fini(void)
{
    PyFloatObject *p;
    PyFloatBlock *list;
    int i;
    int u;

    u = PyFloat_ClearFreeList();

    if (!Py_VerboseFlag)
        return;
    fprintf(stderr, "# cleanup floats");
    if (!u) {
        fprintf(stderr, "\n");
    }
    else {
        fprintf(stderr,
            ": %d unfreed float%s\n",
            u, u == 1 ? "" : "s");
    }
    if (Py_VerboseFlag > 1) {
        list = block_list;
        while (list != NULL) {
            for (i = 0, p = &list->objects[0];
                 i < N_FLOATOBJECTS;
                 i++, p++) {
                if (PyFloat_CheckExact(p) &&
                    Py_REFCNT(p) != 0) {
                    char *buf = PyOS_double_to_string(
                        PyFloat_AS_DOUBLE(p), 'r',
                        0, 0, NULL);
                    if (buf) {


                        fprintf(stderr,
                 "#   <float at %p, refcnt=%ld, val=%s>\n",
                                    p, (long)Py_REFCNT(p), buf);
                                    PyMem_Free(buf);
                            }
                }
            }
            list = list->next;
        }
    }
}
