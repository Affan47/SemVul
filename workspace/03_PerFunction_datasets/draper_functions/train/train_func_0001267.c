UTF16toUTF8(FILE *fp)
{
	FILE *fp8;
	unsigned short t16[512];
	unsigned char t8[2048];
	const UTF16 *p16,*p16a;
	UTF8 *p8;

	if((fp8=tmpfile()) == NULL) return NULL;

#ifdef _WIN32
	 _setmode(_fileno(fp),_O_BINARY);
#endif

	fseek(fp,2,SEEK_SET);
	while(fread(t16,2,1,fp))
	{
		p16 = t16; p8 = t8; p16a = p16+1;
		if(IConvertUTF16toUTF8(&p16,p16a,&p8,t8+2047) == 0)
		{
			if (fwrite(t8,1,(size_t)(p8-t8),fp8) == 0)
				fail(1, "unable to write to temporary file %s", fp8);
		}
		else
			fail(1,"unable to convert Unicode file, illegal or malformed UTF16 sequence");
	}

	fseek(fp8,0,SEEK_SET);

	return fp8;
}
