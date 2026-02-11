write_image_colorscaleCmd(const char *filename)
{
	extern unsigned char *_imageTransform;
	int             i;
	FILE           *fp;
	if (!_imageTransform_exists) {
		err("First `set image grayscale'");
		return false;
	}
	std::string fname(filename);
	un_double_quote(fname);
	if (!strcmp(fname.c_str(), "stdout"))
		fp = stdout;
	else if (!strcmp(fname.c_str(), "stderr"))
		fp = stderr;
	else if (NULL == (fp = fopen(fname.c_str(), "a+"))) {
		err("Sorry, `write image grayscale to \\file' can't open file named in next line");
		err(filename);
		return false;
	}
	for (i = 0; i < 256; i++)
		fprintf(fp, "%g %g %g\n",
			*(_imageTransform + i) / 255.0,
			*(_imageTransform + i + 256) / 255.0,
			*(_imageTransform + i + 512) / 255.0);
	fclose(fp);
	return true;
}
