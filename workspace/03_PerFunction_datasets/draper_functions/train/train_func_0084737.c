dump_cachedir_options(StoreEntry * entry, struct cache_dir_option *options, SwapDir * sd)
{
    struct cache_dir_option *option;
    if (!options)
	return;
    for (option = options; option->name; option++)
	if (option->dump)
	    option->dump(entry, option->name, sd);
}
