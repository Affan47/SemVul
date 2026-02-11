load_images()
{
	int i;

	for (i = 0; i < image_count; i++) {
		images[i].f = input_files[i];
		images[i].s = IMG_Load(input_files[i]);
		if (!images[i].s) {
			fprintf(stderr, "Unable to load image %s: %s\n", input_files[i], IMG_GetError());
			exit(1);
		}
		SDL_SetAlpha(images[i].s, 0, 255);
		SDL_SetColorKey(images[i].s, 0, 0);

		get_offset_for_image(&images[i]);

		images[i].placed = 0;
	}
}
