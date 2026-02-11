cpu_partial_store(struct kmem_cache *s, const char *buf,
				 size_t length)
{
	unsigned long objects;
	int err;

	err = kstrtoul(buf, 10, &objects);
	if (err)
		return err;
	if (objects && !kmem_cache_has_cpu_partial(s))
		return -EINVAL;

	s->cpu_partial = objects;
	flush_all(s);
	return length;
}
