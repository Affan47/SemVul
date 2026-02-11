processfile(hm_list_t *v, const char *filename, int op){
	char buffer[BUFFER_SIZE];

	FILE *f = fopen(filename, "r");

	unsigned int i = 0;
	char *key;
	while( (key = fgets(buffer, BUFFER_SIZE, f)) ){
		trim(key);

		switch(op){
		case 0:
			hm_list_put(v, hm_pair_create(key, key));
			break;
		case 1:
			hm_list_remove(v, key);
			break;
		}

		i++;

		if (i % ( PROCESS_STEP ) == 0){
			printf("Processed %10u...\n", i);
		}
	}

	fclose(f);
}
