perl_netsplit_channel_fill_hash(HV *hv, NETSPLIT_CHAN_REC *rec)
{
	hv_store(hv, "name", 4, new_pv(rec->name), 0);
	hv_store(hv, "op", 2, newSViv(rec->op), 0);
	hv_store(hv, "halfop", 6, newSViv(rec->halfop), 0);
	hv_store(hv, "voice", 5, newSViv(rec->voice), 0);
}
