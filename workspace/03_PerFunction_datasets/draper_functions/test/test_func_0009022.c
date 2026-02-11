fscheck_create_extents_tree(volume* vol)
{
    btree* result = (btree*) ALLOC(btree*, sizeof(btree));
    int    retval = 0;
    if (!result)
    {
	printf("No memory for extents btree\n");
	return FSCK_ERR;
    }
    if (FSCK_FATAL & (retval =
	fscheck_init_extent(result, vol, &vol->vol.ext_file)))
    {
	vol->extents = NULL;
	return retval;
    }
    vol->extents = result;
    return retval;
}
