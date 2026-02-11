switch_free (gpointer mem)
{
    if (mem) {
        if (gnome_keyring_memory_is_secure (mem))
            gnome_keyring_memory_free (mem);
        else
            free (mem);
    }
}
