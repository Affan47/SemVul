writeImage(io::IWriteFile *file, IImage *image, u32 param) const
{
	char cache[70];
	int size;

	const core::dimension2d<u32>& imageSize = image->getDimension();

	const bool binary = false;

	if (binary)
		size = snprintf(cache, 70, "P6\n");
	else
		size = snprintf(cache, 70, "P3\n");

	if (file->write(cache, size) != size)
		return false;

	size = snprintf(cache, 70, "%d %d\n", imageSize.Width, imageSize.Height);
	if (file->write(cache, size) != size)
		return false;

	size = snprintf(cache, 70, "255\n");
	if (file->write(cache, size) != size)
		return false;

	if (binary)
	{
		for (u32 h = 0; h < imageSize.Height; ++h)
		{
			for (u32 c = 0; c < imageSize.Width; ++c)
			{
				const video::SColor& pixel = image->getPixel(c, h);
				const u8 r = (u8)(pixel.getRed() & 0xff);
				const u8 g = (u8)(pixel.getGreen() & 0xff);
				const u8 b = (u8)(pixel.getBlue() & 0xff);
				file->write(&r, 1);
				file->write(&g, 1);
				file->write(&b, 1);
			}
		}
	}
	else
	{
		s32 n = 0;

		for (u32 h = 0; h < imageSize.Height; ++h)
		{
			for (u32 c = 0; c < imageSize.Width; ++c, ++n)
			{
				const video::SColor& pixel = image->getPixel(c, h);
				size = snprintf(cache, 70, "%.3u %.3u %.3u%s", pixel.getRed(), pixel.getGreen(), pixel.getBlue(), n % 5 == 4 ? "\n" : "  ");
				if (file->write(cache, size) != size)
					return false;
			}
		}
	}

	return true;
}
