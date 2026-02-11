read_raw_file_text(char *filename, int mode, char *raw_text)
{
	CFILE	*mf;
	int	file_is_encrypted;
	int file_is_unicode;

	Assert(filename);

	mf = cfopen(filename, "rb", CFILE_NORMAL, mode);
	if (mf == NULL)
	{
		nprintf(("Error", "Wokka!  Error opening file (%s)!\n", filename));
		longjmp(parse_abort, 5);
	}


	int file_len = cfilelength(mf);

	if(!file_len) {
		nprintf(("Error", "Oh noes!!  File is empty! (%s)!\n", filename));
		longjmp(parse_abort, 5);
	}


	allocate_mission_text( file_len + 1 );


	if (raw_text == NULL)
		raw_text = Mission_text_raw;


	cfread(raw_text, MIN(file_len, 10), 1, mf);
	file_is_encrypted = is_encrypted(raw_text);
	cfseek(mf, 0, CF_SEEK_SET);


	file_is_unicode = is_unicode(raw_text);
	if ( file_is_unicode )
	{
		nprintf(("Error", "Wokka!  File (%s) is in Unicode format!\n", filename));
		longjmp(parse_abort, 5);
	}

	if ( file_is_encrypted )
	{
		int	unscrambled_len;
		char	*scrambled_text;
		scrambled_text = (char*)vm_malloc(file_len+1);
		Assert(scrambled_text);
		cfread(scrambled_text, file_len, 1, mf);

		unencrypt(scrambled_text, file_len, raw_text, &unscrambled_len);
		file_len = unscrambled_len;
		vm_free(scrambled_text);
	}
	else
	{
		cfread(raw_text, file_len, 1, mf);
	}


	raw_text[file_len] = '\0';

	cfclose(mf);
}
