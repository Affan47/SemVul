htcoff_init(Bounds *b, File *file, ht_format_group *format_group)
{
	FileOfs h;
	Endianess end;

	if (!is_coff(file, end, h = 0)) {

		byte mz[2];
		file->seek(0);
		if (file->read(mz, 2) != 2) return 0;
		if ((mz[0] != IMAGE_MZ_MAGIC0) || (mz[1] != IMAGE_MZ_MAGIC1) ||
				(!is_coff(file, end, h = 0x800)))
				return 0;
	}

	ht_coff *g = new ht_coff();
	g->init(b, file, htcoff_ifs, format_group, h, end);
	return g;
}
