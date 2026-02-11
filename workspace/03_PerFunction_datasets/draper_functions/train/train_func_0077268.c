move_unreachable(PyGC_Head *young, PyGC_Head *unreachable)
{
    PyGC_Head *gc = young->gc.gc_next;


    while (gc != young) {
        PyGC_Head *next;

        if (gc->gc.gc_refs) {


            PyObject *op = FROM_GC(gc);
            traverseproc traverse = Py_TYPE(op)->tp_traverse;
            assert(gc->gc.gc_refs > 0);
            gc->gc.gc_refs = GC_REACHABLE;
            (void) traverse(op,
                            (visitproc)visit_reachable,
                            (void *)young);
            next = gc->gc.gc_next;
            if (PyTuple_CheckExact(op)) {
                _PyTuple_MaybeUntrack(op);
            }
        }
        else {


            next = gc->gc.gc_next;
            gc_list_move(gc, unreachable);
            gc->gc.gc_refs = GC_TENTATIVELY_UNREACHABLE;
        }
        gc = next;
    }
}
