read_resfile(char *inname)
{
	FILE *fp;
	struct resheader32 rh;
	int is32bit = 1;
	resource_t *top;

	fp = fopen(inname, "rb");
	if(!fp)
            fatal_perror("Could not open %s", inname);


	if(fread(&rh, 1, sizeof(rh), fp) != sizeof(rh))
		is32bit = 0;
	else
	{
		if(!memcmp(&emptyheader, &rh, sizeof(rh)))
			is32bit = 1;
		else if(!memcmp(&emptyheaderSWAPPED, &rh, sizeof(rh)))
			error("Binary .res-file has its byteorder swapped\n");
		else
			is32bit = 0;
	}

	if(is32bit && !win32)
		error("Cannot convert 32-bit .res-file into 16-bit resources (and will, hopefully never, implement it)\n");

	if(!is32bit && win32)
		error("Cannot (yet) convert 16-bit .res-file into 32-bit resources\n");

	if(!is32bit)
	{
		fseek(fp, 0, SEEK_SET);
		top = read_res16(fp);
	}
	else
	{
		top = read_res32(fp);
	}

	fclose(fp);

	return top;
}
