gwy_deserialize_char_array(const guchar *buffer,
                           gsize size,
                           gsize *position,
                           gsize *asize)
{
    guchar *value;
    gsize newasize;

    gwy_debug("buf = %p, size = %" G_GSIZE_FORMAT ", pos = %" G_GSIZE_FORMAT,
              buffer, size, *position);

    g_return_val_if_fail(*position + sizeof(gint32) <= size, NULL);
    if (!(newasize = gwy_deserialize_int32(buffer, size, position)))
        return NULL;
    g_return_val_if_fail(*position + newasize*sizeof(guchar) <= size, NULL);
    value = g_memdup(buffer + *position, newasize*sizeof(guchar));
    *position += newasize*sizeof(guchar);
    *asize = newasize;

    gwy_debug("|value| = %" G_GSIZE_FORMAT, newasize);
    return value;
}
