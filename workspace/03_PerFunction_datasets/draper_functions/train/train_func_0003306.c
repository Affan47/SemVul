VnFileConvert(int inCharset, int outCharset, const char *inFile, const char *outFile)
{
	FILE *inf = NULL;
	FILE *outf = NULL;
	int ret = 0;
	char tmpName[32];

	if (inFile == NULL) {
		inf = stdin;
#if defined(_WIN32)
		_setmode( _fileno(stdin), _O_BINARY);
#endif
	}
	else {
		inf = fopen(inFile, "rb");
		if (inf == NULL) {
			ret = VNCONV_ERR_INPUT_FILE;
			goto end;
		}
	}

	if (outFile == NULL)
		outf = stdout;
	else {

		char outDir[256];
		strcpy(outDir, outFile);

#if defined(_WIN32)
		char *p = strrchr(outDir, '\\');
#else
		char *p = strrchr(outDir, '/');
#endif

		if (p == NULL)
			outDir[0] = 0;
		else
			*p = 0;

		strcpy(tmpName, outDir);
        strcat(tmpName, "XXXXXX");

		if (mkstemp(tmpName) == -1) {
			fclose(inf);
			ret = VNCONV_ERR_OUTPUT_FILE;
			goto end;
		}
		outf = fopen(tmpName, "wb");

		if (outf == NULL) {
			fclose(inf);
			ret = VNCONV_ERR_OUTPUT_FILE;
			goto end;
		}
	}


	ret = vnFileStreamConvert(inCharset, outCharset, inf, outf);
	if (inf != stdin)
		fclose(inf);
	if (outf != stdout) {
		fclose(outf);


		if (ret == 0) {
			remove(outFile);
#if !defined(_WIN32)
			char cmd[256];
			sprintf(cmd, "mv %s %s", tmpName, outFile);
			cmd[0] = system(cmd);
#else
			if (rename(tmpName, outFile) != 0) {
				remove(tmpName);
				ret = VNCONV_ERR_OUTPUT_FILE;
				goto end;
			}
#endif
		}
		else
			remove(tmpName);
	}

end:
#if defined(_WIN32)
	if (inf == stdin) {
		_setmode( _fileno(stdin), _O_BINARY);
	}
#endif
	return ret;
}
