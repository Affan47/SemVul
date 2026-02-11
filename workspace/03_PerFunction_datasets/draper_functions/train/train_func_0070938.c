cmap_load(char *filename)
{
    int err;


    if ((err = cmap_load_internal(filename)) != 0)
        return err;


    if (filename != 0)
        S_cmap_loaded = TRUE;


    return 0;
}
