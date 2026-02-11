crd_load(int in_fd, int out_fd, decompress_fn deco)
{
	int result;
	crd_infd = in_fd;
	crd_outfd = out_fd;

	if (!deco) {
		pr_emerg("Invalid ramdisk decompression routine.  "
			 "Select appropriate config option.\n");
		panic("Could not decompress initial ramdisk image.");
	}

	result = deco(NULL, 0, compr_fill, compr_flush, NULL, NULL, error);
	if (decompress_error)
		result = 1;
	return result;
}
