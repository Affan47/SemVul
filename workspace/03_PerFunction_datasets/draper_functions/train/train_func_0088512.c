v4l2_unmap_buffers(int index)
{
	unsigned int i;


	for (i = 0; i < devices[index].no_frames; i++) {
		if (devices[index].frame_pointers[i] != MAP_FAILED) {
			SYS_MUNMAP(devices[index].frame_pointers[i],
					devices[index].frame_sizes[i]);
			devices[index].frame_pointers[i] = MAP_FAILED;
			V4L2_LOG("unmapped buffer %u\n", i);
		}
	}
}
