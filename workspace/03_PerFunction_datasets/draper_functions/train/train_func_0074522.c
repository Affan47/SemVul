svg_check_download(SVGIn *svgin)
{
	u64 size;
	FILE *f = gf_f64_open(svgin->file_name, "rb");
	if (!f) return 0;
	gf_f64_seek(f, 0, SEEK_END);
	size = gf_f64_tell(f);
	fclose(f);
	if (size==svgin->file_size) return 1;
	return 0;
}
