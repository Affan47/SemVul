open_file(char *mode,char *nom){

	FILE *fitxer;
	fitxer=fopen(nom,mode);
		if(fitxer==NULL)
	   {
	   printf( "cannot open file %s.\n",nom );
	   abort();
	   }

	return fitxer;

}
