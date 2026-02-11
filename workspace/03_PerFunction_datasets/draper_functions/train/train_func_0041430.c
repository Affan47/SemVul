PyArena_New()
{
    PyArena* arena = (PyArena *)PyMem_Malloc(sizeof(PyArena));
    if (!arena)
        return (PyArena*)PyErr_NoMemory();

    arena->a_head = block_new(DEFAULT_BLOCK_SIZE);
    arena->a_cur = arena->a_head;
    if (!arena->a_head) {
        PyMem_Free((void *)arena);
        return (PyArena*)PyErr_NoMemory();
    }
    arena->a_objects = PyList_New(0);
    if (!arena->a_objects) {
        block_free(arena->a_head);
        PyMem_Free((void *)arena);
        return (PyArena*)PyErr_NoMemory();
    }
#if defined(Py_DEBUG)
    arena->total_allocs = 0;
    arena->total_size = 0;
    arena->total_blocks = 1;
    arena->total_block_size = DEFAULT_BLOCK_SIZE;
    arena->total_big_blocks = 0;
#endif
    return arena;
}
