compute_container_size(u8 *data, u32 total_size)
{
	size_t size = 0;
	u32 *header = (u32 *)data;

	if (header[0] != UCODE_MAGIC ||
	    header[1] != UCODE_EQUIV_CPU_TABLE_TYPE ||
	    header[2] == 0)
		return size;

	size = header[2] + CONTAINER_HDR_SZ;
	total_size -= size;
	data += size;

	while (total_size) {
		u16 patch_size;

		header = (u32 *)data;

		if (header[0] != UCODE_UCODE_TYPE)
			break;


		patch_size = header[1];
		if (patch_size > PATCH_MAX_SIZE)
			break;

		size	   += patch_size + SECTION_HDR_SIZE;
		data	   += patch_size + SECTION_HDR_SIZE;
		total_size -= patch_size + SECTION_HDR_SIZE;
	}

	return size;
}
