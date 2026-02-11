compress_file(char* input_filename, char* output_filename)
{
	U64 filesize = 0;
	U64 compressedfilesize = ARCHIVE_MAGICNUMBER_SIZE;
	char* in_buff;
	char* out_buff;

	char stdinout[] = "std";

	FILE* finput;
	if (!strcmp (input_filename, stdinout)) {
		fprintf(stderr, "Using stdin for input\n");
		finput = stdin;
	} else {
		finput = fopen( input_filename, "rb" );
	}

	FILE* foutput;
	if (!strcmp (output_filename, stdinout)) {
		fprintf(stderr, "Using stdout for output\n");
		foutput = stdout;
	} else {
		foutput = fopen( output_filename, "wb" );
	}

	if ( finput==0 ) { printf("Pb opening %s\n", input_filename);  return 2; }
	if ( foutput==0) { printf("Pb opening %s\n", output_filename); return 3; }


	in_buff = malloc(CHUNKSIZE);
	out_buff = malloc(OUT_CHUNKSIZE);


	*(U32*)out_buff = ARCHIVE_MAGICNUMBER;
	fwrite(out_buff, 1, ARCHIVE_MAGICNUMBER_SIZE, foutput);


	while (1)
	{
		int outSize;

	    int inSize = fread(in_buff, 1, CHUNKSIZE, finput);
		if( inSize<=0 ) break;
		filesize += inSize;


		outSize = LZ4_compress(in_buff, out_buff+4, inSize);
		* (U32*) out_buff = outSize;
		compressedfilesize += outSize+4;


		fwrite(out_buff, 1, outSize+4, foutput);
	}


	fprintf(stderr, "Compressed %llu bytes into %llu bytes ==> %.2f%%\n",
		(unsigned long long) filesize, (unsigned long long) compressedfilesize, (double)compressedfilesize/filesize*100);

	fclose(finput);
	fclose(foutput);

	return 0;
}
