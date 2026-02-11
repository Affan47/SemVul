multimaster_mtnode_extension_destructor (void* ext, void *object, void *parent)
{
    if (ext)
    {
        multimaster_mtnode_extension *mtnode_ext = (multimaster_mtnode_extension *)ext;
        if (mtnode_ext->replica)
        {
            object_release (mtnode_ext->replica);
            mtnode_ext->replica = NULL;
        }
	slapi_ch_free((void **)&ext);
    }
}
