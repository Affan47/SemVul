gg_image_prepare_to_png_by_strip (const gGraphStripImagePtr img,
				  FILE * file, int compression_level,
				  int quantization_factor)
{

    if (img->pixel_format == GG_PIXEL_PALETTE)
	return image_prepare_to_png_palette_by_strip (img, file,
						      compression_level);
    if (img->pixel_format == GG_PIXEL_GRAYSCALE)
	return image_prepare_to_png_grayscale_by_strip (img, file,
							compression_level,
							quantization_factor);
    if (img->pixel_format == GG_PIXEL_RGBA || img->pixel_format == GG_PIXEL_ARGB
	|| img->pixel_format == GG_PIXEL_BGRA)
	return image_prepare_to_png_rgba_by_strip (img, file, compression_level,
						   quantization_factor);
    return image_prepare_to_png_rgb_by_strip (img, file, compression_level,
					      quantization_factor);
}
