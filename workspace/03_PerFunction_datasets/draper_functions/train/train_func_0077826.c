action_compress_image(void)
{
	struct Image* imagep = image_load(input_path);
	printf("Picture dimensions: %dx%d\n", imagep->width,
			imagep->height);
	uint64_t length = 0;
	uint64_t result = 0;
	uint8_t* data = compress_image_full(imagep, quality,
			(uint64_t*) &length);

	printf("Saving %lu bytes to %s...", (long unsigned int) length, output_path);

	result = write_file(output_path, data, length);

	if (result == length) {
		printf("OK!\n");

	} else {
		printf("ERROR: Only wrote %lu bytes!\n", result);
	}

	if (length > 0)
		free(data);

	image_del(imagep);
}
