readParameters(){

	FILE* in = fopen("data/config.ini","r");
	if(in){
		static int readFirstTime = 1;


		char key[200],value[200];
		while(fscanf(in,"%s%s",key,value)!=EOF){
			if(strcmp(key,"USE_RANSAC")==0){
				USE_RANSAC = readInt(value);

			}
			else if(strcmp(key,"RANSAC_SAMPLES")==0){
				RANSAC_SAMPLES = readInt(value);

			}
			else if(strcmp(key,"RANSAC_DISTANCE_THRESHOLD")==0){
				RANSAC_DISTANCE_THRESHOLD = readDouble(value);
			}
			else if(strcmp(key,"RANSAC_ITERATIONS")==0){
				RANSAC_ITERATIONS = readInt(value);
			}
			else if(strcmp(key,"CAMERA_INDEX")==0){
				chosenCamera = readInt(value);
			}
			else if(strcmp(key,"OPEN_MOVIE")==0){
				string strValue = readString(value);

				sprintf(movieFile,"%s",(char*)strValue.c_str());
			}


		}

		if(readFirstTime){
			readFirstTime = 0;
			printf("Reading values from data/config.ini\n");
			printf("USE_RANSAC: %d\n",USE_RANSAC);
			printf("RANSAC_SAMPLES: %d\n",RANSAC_SAMPLES);
			printf("RANSAC_DISTANCE_THRESHOLD: %d\n",RANSAC_DISTANCE_THRESHOLD);
			printf("RANSAC_ITERATIONS: %d\n",RANSAC_ITERATIONS);
			printf("CAMERA_INDEX: %d\n",chosenCamera);
			printf("Opening movie file: %s.%d\n",movieFile,&movieFile);
		}

		fclose(in);
	}
	else{
		printf("Using default parameters. If you wish to use a configuration file, put it in data/config.ini\n");
		sprintf(movieFile,"NO");
	}

}
