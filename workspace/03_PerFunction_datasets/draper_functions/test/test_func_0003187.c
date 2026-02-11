sony_find_snc_handle(int handle)
{
	int i;


	if (!handles || !handle)
		return -EINVAL;

	for (i = 0; i < 0x10; i++) {
		if (handles->cap[i] == handle) {
			dprintk("found handle 0x%.4x (offset: 0x%.2x)\n",
					handle, i);
			return i;
		}
	}
	dprintk("handle 0x%.4x not found\n", handle);
	return -EINVAL;
}
