enum_replace(char *ptr, struct trace_enum_map *map, int len)
{
	int rlen;
	int elen;


	elen = snprintf(ptr, 0, "%ld", map->enum_value);

	if (len < elen)
		return NULL;

	snprintf(ptr, elen + 1, "%ld", map->enum_value);


	rlen = strlen(ptr + len);
	memmove(ptr + elen, ptr + len, rlen);

	ptr[elen + rlen] = 0;

	return ptr + elen;
}
