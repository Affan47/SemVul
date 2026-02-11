decrypt(char *key, char *tablefile, FILE *fp){

	if(strlen(key) != 16){
		fprintf(stderr, "Invalid length of key\n") ;
		exit(0) ;
	}

	keySchedule(key, SKey, SKeyDec) ;
	unsigned char byte_8[8] ;
	unsigned char out_8[8] ;


	int printF = 1 ;
	while(!feof(fp)){
		memset(byte_8, 0, 8) ;
		int bytes_read = fread(byte_8,1, 8, fp) ;
		if(feof(fp))
			break ;
		if (bytes_read > 0){
			crypt(byte_8, SKeyDec, out_8, printF) ;
			if(printF)
				printF = 0 ;
			for (int i=0 ; i < 8 ; ++i)
				printf("%c", out_8[i]) ;
		}
	}
}
