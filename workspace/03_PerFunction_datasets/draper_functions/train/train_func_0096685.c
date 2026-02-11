switch_realloc (gpointer mem, gsize size)
{
    gpointer p;

    if (size == 0) {
        free (mem);
        return NULL;
    }

    if (!mem) {
        if (seahorse_use_secure_mem)
            p = gnome_keyring_memory_alloc (size);
        else
            p = malloc (size);
    } else if (gnome_keyring_memory_is_secure (mem))
        p = gnome_keyring_memory_try_realloc (mem, size);
    else
        p = realloc (mem, size);
    return p;
}
