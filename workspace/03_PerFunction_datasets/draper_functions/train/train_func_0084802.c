starfield_generate_bitmap_buffers()
{
	int idx;

	int sb_instances = (int)Starfield_bitmap_instances.size();

	for (idx = 0; idx < sb_instances; idx++) {
		if (Starfield_bitmap_instances[idx].star_bitmap_index < 0) {
			continue;
		}

		starfield_create_bitmap_buffer(idx);
	}
}
