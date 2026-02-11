cleanup (void)
{
    if (lock_path)
        unlink (lock_path);
    if (xserver)
        g_object_unref (xserver);
}
