file_partition(char *c_dir, FILE *f_in, int_text k, int_text r){

	char c_in[FILE_NAME];
	sprintf(c_in, "%sall.in", c_dir);

	FILE* f_all = fopen(c_in, "w");
	if(!f_all) perror ("open_input");
	fseek(f_all, 0, SEEK_SET);


	char c_aux[FILE_READ];


	sprintf(c_aux, "%spartition/", c_dir);
	mkdir(c_aux);


	int_text i = 0;
	int_text j = 0, total = 0;
	for(; i< r && total < k; i++){

		sprintf(c_in, "%spartition/%d.fasta", c_dir, i);

		FILE* f_aux = fopen(c_in, "w");
		if(!f_aux) perror ("partition");
		fseek(f_aux, 0, SEEK_SET);

		sprintf(c_in, "partition/%d.fasta", i);
		fprintf(f_all,"%s\n", c_in);


		j=0;

		while(fgets(c_aux, FILE_READ, f_in)){


			fprintf(f_aux,"%s", c_aux);

			fgets(c_aux, FILE_READ, f_in);
			fprintf(f_aux,"%s", c_aux);

			fgets(c_aux, FILE_READ, f_in);
			fprintf(f_aux,"%s", c_aux);

			fgets(c_aux, FILE_READ, f_in);
			fprintf(f_aux,"%s", c_aux);

			j++;
			total++;
			if(j>k/r || total >= k){
				break;
			}
		}
		fclose(f_aux);
	}
	fclose(f_all);


return i;
}
