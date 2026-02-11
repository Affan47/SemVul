load_image(struct image *img, const char *filename, int use_offset_file)
{
	load_image_surface(img, filename, use_offset_file);

	if (use_open_gl && (img->w > gl_max_texture_size || img->h > gl_max_texture_size)) {
		ErrorMessage(__FUNCTION__, "Your system only supports %dx%d textures. Image %s is %dx%d and therefore cannot be used as an OpenGL texture.\n", NO_NEED_TO_INFORM, IS_WARNING_ONLY, gl_max_texture_size, gl_max_texture_size, filename, img->w, img->h);
		return;
	}

	if (use_open_gl) {

		make_texture_out_of_surface(img);
	}
}
