set_storage_sizes_exact(ft_size size1, ft_size size2)
{
    int err = 0;
    if (!this_replaying)
        err = do_write((ft_ull) size1, (ft_ull) size2);
    return err;
}
