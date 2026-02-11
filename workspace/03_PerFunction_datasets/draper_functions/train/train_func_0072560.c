mame_fwrite(mame_file *file, const void *buffer, UINT32 length)
{

	switch (file->type)
	{
		case PLAIN_FILE:
			return osd_fwrite(file->file, buffer, length);
	}

	return 0;
}
