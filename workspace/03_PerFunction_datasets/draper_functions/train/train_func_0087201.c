PyTuple_Fini(void)
{
#if PyTuple_MAXSAVESIZE > 0


    Py_XDECREF(free_list[0]);
    free_list[0] = NULL;

    (void)PyTuple_ClearFreeList();
#endif
#ifdef SHOW_TRACK_COUNT
    show_track();
#endif
}
