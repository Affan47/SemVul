push_macro(pp_entry_t *ppp)
{
	if(macexpstackidx >= MAXMACEXPSTACK)
	{
		ppy_error("Too many nested macros");
		return;
	}

	macexpstack[macexpstackidx] = pp_xmalloc(sizeof(macexpstack[0][0]));
	if(!macexpstack[macexpstackidx])
		return;
        memset( macexpstack[macexpstackidx], 0, sizeof(macexpstack[0][0]));
	macexpstack[macexpstackidx]->ppp = ppp;
	macexpstackidx++;
}
