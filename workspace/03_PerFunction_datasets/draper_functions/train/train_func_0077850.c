evmap_io_init(struct evmap_io *entry)
{
	LIST_INIT(&entry->events);
	entry->nread = 0;
	entry->nwrite = 0;
	entry->nclose = 0;
}
