get_param_pointer(const guchar *buffer, gsize size,
                  guint32 pos, guint32 len,
                  const guchar *name,
                  GError **error)
{
    if (pos < HEADER_SIZE || pos > size - len) {
        err_INVALID(error, name);
        return NULL;
    }
    return buffer + pos;
}
