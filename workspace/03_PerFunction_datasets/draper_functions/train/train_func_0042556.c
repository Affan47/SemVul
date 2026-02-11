seek_value(int prefix, FILE *fp, unsigned int value, struct refdes_ *db)
	{
	fpos_t filepos;
	int ret;
	struct refdes_ refdes;
	char buff[BUFFSIZE];

	fgetpos(fp, &filepos);
	rewind(fp);
	while((ret=get_refdes_from_file(fp, &refdes, buff))!=END_OF_FILE)
		{
		if(ret==REFDES_WITH_VALUE && prefix==refdes_lookup(db, &refdes) && refdes.value==value)
			{
			fsetpos(fp,&filepos);
			return VALUE_FOUND;
			}
		}
	fsetpos(fp,&filepos);
	return VALUE_NOT_FOUND;
	}
