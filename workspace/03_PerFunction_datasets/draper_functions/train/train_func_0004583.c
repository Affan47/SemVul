storeUfsDirReconfigure(SwapDir * sd, int index, char *path)
{
    int i;
    int size;
    int l1;
    int l2;

    i = GetInteger();
    size = i << 10;
    if (size <= 0)
	fatal("storeUfsDirReconfigure: invalid size value");
    i = GetInteger();
    l1 = i;
    if (l1 <= 0)
	fatal("storeUfsDirReconfigure: invalid level 1 directories value");
    i = GetInteger();
    l2 = i;
    if (l2 <= 0)
	fatal("storeUfsDirReconfigure: invalid level 2 directories value");


    if (size == sd->max_size)
	debug(3, 1) ("Cache dir '%s' size remains unchanged at %d KB\n",
	    path, size);
    else
	debug(3, 1) ("Cache dir '%s' size changed to %d KB\n",
	    path, size);
    sd->max_size = size;

    parse_cachedir_options(sd, options, 1);
}
