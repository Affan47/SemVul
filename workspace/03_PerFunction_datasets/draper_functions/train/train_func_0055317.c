tag_tuple_read (Tuple * tuple, VFSFile * handle)
{
    tag_module_t * module = find_tag_module (handle, TAG_TYPE_NONE);

    if (module == NULL)
        return FALSE;

    return module->read_tag (tuple, handle);
}
