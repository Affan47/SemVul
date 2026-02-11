createImageFromFile(io::IReadFile* file)
{
	if (!file)
		return 0;

	IImage* image = 0;

	u32 i;


	for (i=0; i<SurfaceLoader.size(); ++i)
	{
		if (SurfaceLoader[i]->isALoadableFileExtension(file->getFileName()))
		{

			file->seek(0);
			image = SurfaceLoader[i]->loadImage(file);
			if (image)
				return image;
		}
	}


	for (i=0; i<SurfaceLoader.size(); ++i)
	{

		file->seek(0);
		if (SurfaceLoader[i]->isALoadableFileFormat(file))
		{
			file->seek(0);
			image = SurfaceLoader[i]->loadImage(file);
			if (image)
				return image;
		}
	}

	return 0;
}
