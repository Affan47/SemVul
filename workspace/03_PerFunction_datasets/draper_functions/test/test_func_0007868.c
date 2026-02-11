check_if_over(FILE *fp){
char * buf = (char *) malloc(sizeof(char)*MAXCHAR);
char * bf ;
	if (fgets(buf,MAXCHAR,fp) == NULL){
		free(buf);
		return -1;
	}

	bf = getword(&buf) ;

	if ( 	strcmp("ERROR",bf)  != 0 ){
		free(bf);
		return 0;
	}
	else {
		free(bf);
		getword(&buf);
		bf = getword(&buf);
		if ( strcmp("slew",bf) != 0){
			free(bf);
			return  -1;
		}
		else return 1;

	}

	return 1;

}
