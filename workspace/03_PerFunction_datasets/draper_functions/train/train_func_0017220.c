vfs_ungetc(int c, VFSFile *file)
{
    g_return_val_if_fail (file && file->sig == VFS_SIG, EOF);

    if (verbose)
        logger ("VFS: <%p> ungetc\n", file);

    return file->base->vfs_ungetc_impl(c, file);
}
