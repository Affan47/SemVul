randomize_buffer(char *buffer,int buffer_size){
	FILE *fp;
	int x;
	int seed;


	fp=fopen("/dev/urandom","r");
	if(fp!=NULL){
		seed=fgetc(fp);
		fclose(fp);
	        }


	else
		seed=(int)time(NULL);

	srand(seed);
	for(x=0;x<buffer_size;x++)
		buffer[x]=(int)'0'+(int)(72.0*rand()/(RAND_MAX+1.0));

	return;
        }
