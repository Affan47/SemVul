mapset_message(const char *mapset)
{
    if (printfile(filename(".message", mapset)))
	hit_return();

    return 0;
}
