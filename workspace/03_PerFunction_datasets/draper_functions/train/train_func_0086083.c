printcodeseg(FILE* f, unsigned int ds, unsigned int s,
				const char **func_table, int funsize, int extended)
{
	long pos;
	unsigned int size;
	unsigned int externsize;
	unsigned int i;
	unsigned int offset;
	unsigned int nbytes;
	unsigned char* p;
	unsigned char* pp;
	unsigned char* pdata;
	unsigned short* pextern;
	pos = ftell(f);
	if (extended == 0) {
		size = s - ds - sizeof(unsigned short);
	} else {
		size = s - ds - sizeof(unsigned int);
	}

	pp = p = malloc(size);
	pdata = malloc(ds);
	fread(pdata, 1, ds, f);
	printf("\t\t.code\n");
	fread(p, 1, size, f);
	fseek(f, pos, SEEK_SET);

	if( size < 3 * sizeof(unsigned short) )
	{
		printf("Code segment bad!\n");
		free(p);
		free(pdata);
		return;
	}

	printf("\t\t.argc %04XH\n", *(unsigned short*)pp);
	pp += sizeof(unsigned short);

	printf("\t\t.localc %04XH\n", *(unsigned short*)pp);
	pp += sizeof(unsigned short);

	externsize = *(unsigned short*)pp;
	printf("\t\t.externsize %04XH\n", externsize);
	pp += sizeof(unsigned short);
	if( size < ( ( 3 + externsize ) * sizeof(unsigned short) ) )
	{
		printf("Code segment bad!\n");
		free(p);
		free(pdata);
		return;
	}
	size -= ( ( 3 + externsize ) * sizeof(unsigned short) );
	pextern = (unsigned short*)pp;
	for( i = 0; i < externsize; i++ )
	{
		printf("\t\t.extern %04XH\n", *(unsigned short*)pp);
		pp += sizeof(unsigned short);
	}
	offset = 0;

	while( offset < size )
	{
		nbytes = print_opcode(pp, offset, pdata, pextern, externsize,
						func_table, funsize);
		pp += nbytes;
		offset += nbytes;
	}
	free(p);
	free(pdata);
}
