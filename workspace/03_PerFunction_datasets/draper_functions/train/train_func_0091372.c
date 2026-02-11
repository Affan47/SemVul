il_region_command(flags)
    int flags;
{
    size_t region_start;
    size_t region_end;
    size_t region_size;


    if (il->mark == il->point)
	return;


    if (il->mark > il->point)
    {
	region_start = il->point;
	region_end   = il->mark;
    }
    else
    {
	region_start = il->mark;
	region_end   = il->point;
    }

    region_size = region_end - region_start;

    if (flags & IL_STORE)
    {
	if (il->kill_ring)
	    xfree(il->kill_ring);

	il->kill_ring = xmalloc(region_size + 1);
	memcpy(il->kill_ring, il->buffer + region_start, region_size);
	il->kill_ring[region_size] = '\0';
    }

    if (flags & IL_KILL)
    {
	il->dynamic_length -= region_size;
	il->length         -= region_size;
	il->point           = region_start;
	il->mark            = region_start;
	strcpy(il->buffer + region_start, il->buffer + region_end);
	IL_RESIZE(il->length + 1);
    }
}
