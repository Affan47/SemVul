file_read_tuple (const char * filename, PluginHandle * decoder)
{
    InputPlugin * ip = plugin_get_header (decoder);
    g_return_val_if_fail (ip, NULL);
    g_return_val_if_fail (ip->probe_for_tuple, NULL);

    VFSFile * handle = vfs_fopen (filename, "r");
    Tuple * tuple = ip->probe_for_tuple (filename, handle);

    if (handle)
        vfs_fclose (handle);

    return tuple;
}
