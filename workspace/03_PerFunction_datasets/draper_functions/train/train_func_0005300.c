gf_isom_text_dump(GF_ISOFile *the_file, u32 track, FILE *dump, u32 dump_type)
{
	switch (dump_type) {
	case 2:
		return gf_isom_dump_svg_track(the_file, track, dump);
	case 1:
		return gf_isom_dump_srt_track(the_file, track, dump);
	default:
		return gf_isom_dump_ttxt_track(the_file, track, dump);
	}
}
