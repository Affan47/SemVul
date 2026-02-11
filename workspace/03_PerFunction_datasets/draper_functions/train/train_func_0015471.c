PyArena_Free(PyArena *arena)
{
    assert(arena);
#if defined(Py_DEBUG)


#endif
    block_free(arena->a_head);


    Py_DECREF(arena->a_objects);
    free(arena);
}
