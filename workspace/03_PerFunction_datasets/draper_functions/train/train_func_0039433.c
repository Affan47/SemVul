sha_init(SHAObject* self, PyObject* args, PyObject* kwds)
{
    if (Init(&self->hash_state, (int)self->digest_size * 8) != SUCCESS)
    {
        PyErr_SetString(PyExc_RuntimeError, "failed to initialize hash state");
        return -1;
    }

    return 0;
}
