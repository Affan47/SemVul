testHASH() {

	int rand, key;
	FILE *fp, *fr;
	char rand_line[10];
	char key_line[10];
	struct timeval start, end;
	struct hashtb *newht;
	newht=NULL;

	newht=hashtb_create();

	fp=fopen("rand_data.txt","r");
	fr=fopen("rand_keys.txt","r");

	gettimeofday(&start,NULL);

	while(fgets(rand_line,10,fp) != NULL && fgets(key_line,10,fr) != NULL ) {
		sscanf(rand_line, "%d", &rand);
		sscanf(key_line, "%d", &key);
		hashtb_add_element(newht,key,rand);
	}
	fclose(fp);
	rewind(fr);
	while(fgets(key_line,10,fr) != NULL) {
		sscanf(key_line, "%d", &key);
		hashtb_lookup(newht,key);
	}
	fclose(fr);
	gettimeofday(&end,NULL);
  free(newht);
	printf("Total time: %ld microseconds\n", ((end.tv_sec * 1000000 + end.tv_usec)
		  - (start.tv_sec * 1000000 + start.tv_usec)));
	printf("Test complete!\n");
}
