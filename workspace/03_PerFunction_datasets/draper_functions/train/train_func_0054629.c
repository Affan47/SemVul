nbt_dump_binary(const nbt_node* tree)
{
    errno = NBT_OK;

    if(tree == NULL) return BUFFER_INIT;

    struct buffer ret = BUFFER_INIT;

    errno = __dump_binary(tree, true, &ret);

    return ret;
}
