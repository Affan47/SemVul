get_file_size(const char *fname)
{
	if (is_null_entry(fname))
		return 0;

	const char *mode = "rb";
	bool text = is_text_file(fname);
	if (text)
		mode = "r";

	FILE *fp;
	try {
		fp = U7open (fname, mode);
	} catch (const file_open_exception& e) {
		cerr << e.what() << endl;
		exit(1);
	}

	long len = 0;
	if (!text)
	{
		fseek(fp, 0, SEEK_END);
		len = ftell(fp);
	}
	else while (fgetc(fp) != EOF)
		len++;

	fclose(fp);
	return len;
}
