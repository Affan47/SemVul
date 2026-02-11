pysqlite_cache_dealloc(pysqlite_Cache* self)
{
    pysqlite_Node* node;
    pysqlite_Node* delete_node;

    if (!self->factory) {

        return;
    }


    node = self->first;
    while (node) {
        delete_node = node;
        node = node->next;
        Py_DECREF(delete_node);
    }

    if (self->decref_factory) {
        Py_DECREF(self->factory);
    }
    Py_DECREF(self->mapping);

    Py_TYPE(self)->tp_free((PyObject*)self);
}
