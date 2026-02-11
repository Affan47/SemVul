file_open_input(t_TEXT **Text, char *c_dir, char *c_file, int_text *k, int_text *r){

	char c_aux[FILE_NAME];
	sprintf(c_aux, "%s%s", c_dir, c_file);

	printf("input = %s\n", c_aux);

	FILE* f_aux = fopen(c_aux, "r");
	if(!f_aux) perror ("open_input");
	fseek(f_aux, 0, SEEK_SET);

	#if INPUT_CAT

		*r = file_partition(c_dir, f_aux, *k, *r);
		fclose(f_aux);

		sprintf(c_aux, "%sall.in", c_dir);
		f_aux = fopen(c_aux, "r");
		if(!f_aux) perror ("open_input");
		fseek(f_aux, 0, SEEK_SET);

		*k = *r;
	#endif

	*Text = (t_TEXT*) malloc(sizeof(t_TEXT) * (*k));

	int_text i = 0;
	for(; i < *k; i++){

		(*Text)[i].c_file = (char*) malloc(FILE_NAME*sizeof(char));

		#if INPUT_CAT
			(*Text)[i].n_strings = 0;
		#endif

		fscanf(f_aux, "%s\n", c_aux);
		sprintf((*Text)[i].c_file, "%s%s", c_dir, c_aux);

	}

	fclose(f_aux);
	printf("\n");

return 0;
}
