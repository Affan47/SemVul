IMAGE_get_pixel_format(GB_IMG *image)
{
	if ((image->format == GB_IMAGE_RGBA) || (image->format == GB_IMAGE_RGBX))
		return GL_RGBA;

	else if ((image->format == GB_IMAGE_BGRA) || (image->format == GB_IMAGE_BGRX))
		return GL_BGRA;
	else if (image->format == GB_IMAGE_RGB)
		return GL_RGB;
	else if (image->format == GB_IMAGE_BGR)
		return GL_BGR;
	else
		return 0;
}
