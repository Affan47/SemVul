clear_scan(wchar_t *longname, int use_longname,
		       struct scan_state *s)
{
	s->shortmatch = s->longmatch = s->slot = -1;
	s->free_end = s->got_slots = s->free_start = 0;

	if (use_longname & 1)
		s->size_needed = 1 +
			(wcslen(longname) + VSE_NAMELEN - 1)/VSE_NAMELEN;
	else
                s->size_needed = 1;
}
