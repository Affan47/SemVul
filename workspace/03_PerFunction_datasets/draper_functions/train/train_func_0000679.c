chmod (const char *path, mode_t mode)
{
    if (!libc_chmod)
        clickpreload_init ();

    clickpreload_assert_path_in_instdir ("chmod", path);
    mode |= S_IWUSR;
    return (*libc_chmod) (path, mode);
}
