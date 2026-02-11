enc_jump(const char mnemonic[])
{
	if(strcmp(mnemonic, "") == 0) {
		fprintf(pOutfile,"000");
		if(settings.code != 0) { printf("000"); }
		return 1;
	} else if(strcmp(mnemonic, "JGT") == 0) {
		fprintf(pOutfile,"001");
		if(settings.code != 0) { printf("001"); }
		return 1;
	} else if(strcmp(mnemonic, "JEQ") == 0) {
		fprintf(pOutfile,"010");
		if(settings.code != 0) { printf("010"); }
		return 1;
	} else if(strcmp(mnemonic, "JGE") == 0) {
		fprintf(pOutfile,"011");
		if(settings.code != 0) { printf("011"); }
		return 1;
	} else if(strcmp(mnemonic, "JLT") == 0) {
		fprintf(pOutfile,"100");
		if(settings.code != 0) { printf("100"); }
		return 1;
	} else if(strcmp(mnemonic, "JNE") == 0) {
		fprintf(pOutfile,"101");
		if(settings.code != 0) { printf("101"); }
		return 1;
	} else if(strcmp(mnemonic, "JLE") == 0) {
		fprintf(pOutfile,"110");
		if(settings.code != 0) { printf("110"); }
		return 1;
	} else if(strcmp(mnemonic, "JMP") == 0) {
		fprintf(pOutfile,"111");
		if(settings.code != 0) { printf("111"); }
		return 1;
	} else {
		int i = find_line_num();
		line_notification(i);
		exit_error(11, "Symbol Not Found In Jump Lookup Table.");
	}
	return 0;
}
