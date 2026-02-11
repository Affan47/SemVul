kvp_value_new_binary_nc(void * value, guint64 datasize)
{
    KvpValue * retval;
    if (!value) return NULL;

    retval = g_new0(KvpValue, 1);
    retval->type = KVP_TYPE_BINARY;
    retval->value.binary.data = value;
    retval->value.binary.datasize = datasize;
    return retval;
}
