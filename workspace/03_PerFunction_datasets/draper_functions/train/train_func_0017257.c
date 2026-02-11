vfs_ftruncate (VFSFile * file, int64_t length)
{
    g_return_val_if_fail (file && file->sig == VFS_SIG, -1);

    if (verbose)
        logger ("VFS: <%p> truncate to %"PRId64"\n", file, length);

    return file->base->vfs_ftruncate_impl(file, length);
}
