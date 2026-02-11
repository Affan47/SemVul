check_dumpfile_size(char *file)
{
	int i;
	struct stat64 stat;
	struct pt_load_segment *pls;
	uint64_t segment_end;

	if (stat64(file, &stat) < 0)
		return;

	for (i = 0; i < nd->num_pt_load_segments; i++) {
		pls = &nd->pt_load_segments[i];

		segment_end = pls->file_offset +
			(pls->phys_end - pls->phys_start);

		if (segment_end > stat.st_size) {
			error(WARNING, "%s: may be truncated or incomplete\n"
				"         PT_LOAD p_offset: %lld\n"
				"                 p_filesz: %lld\n"
				"           bytes required: %lld\n"
				"            dumpfile size: %lld\n\n",
				file, pls->file_offset,
				pls->phys_end - pls->phys_start,
				segment_end, stat.st_size);
			return;
		}
	}
}
