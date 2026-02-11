gf_isom_make_interleave(GF_ISOFile *file, Double TimeInSec)
{
	GF_Err e;
	if (gf_isom_get_mode(file) < GF_ISOM_OPEN_EDIT) return GF_BAD_PARAM;
	e = gf_isom_set_storage_mode(file, GF_ISOM_STORE_INTERLEAVED);
	if (e) return e;
	return gf_isom_set_interleave_time(file, (u32) (TimeInSec * gf_isom_get_timescale(file)));
}
