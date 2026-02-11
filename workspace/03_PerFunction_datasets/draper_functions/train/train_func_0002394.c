gwy_deserialize_object_hash(const guchar *buffer,
                            gsize size,
                            gsize *position,
                            const guchar *object_name,
                            gsize *nitems)
{
    gsize mysize;
    GwySerializeItem *items;

    mysize = gwy_serialize_check_string(buffer, size, *position, object_name);
    g_return_val_if_fail(mysize, NULL);
    *position += mysize;

    mysize = gwy_deserialize_int32(buffer, size, position);
    g_return_val_if_fail(mysize <= size - *position, NULL);
    items = gwy_deserialize_hash_items(buffer + *position, mysize, nitems);
    *position += mysize;

    return items;
}
