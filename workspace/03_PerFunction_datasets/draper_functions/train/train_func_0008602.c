main(int argc, char* argv[]) {
	if (argc < 7) {
		printf("Usage: rsem-run-gibbs reference_name sample_name sampleToken BURNIN CHAINLEN GAP [-q]\n");
		exit(-1);
	}

	BURNIN = atoi(argv[4]);
	CHAINLEN = atoi(argv[5]);
	GAP = atoi(argv[6]);
	sprintf(imdName, "%s.temp/%s", argv[2], argv[3]);
	sprintf(statName, "%s.stat/%s", argv[2], argv[3]);
	load_data(argv[1], statName, imdName);

	quiet = false;
	if (argc > 7 && !strcmp(argv[7], "-q")) {
		quiet = true;
	}
	verbose = !quiet;

	init();
	Gibbs(imdName);

	sprintf(modelF, "%s.model", statName);
	FILE *fi = fopen(modelF, "r");
	if (fi == NULL) { fprintf(stderr, "Cannot open %s!\n", modelF); exit(-1); }
	fscanf(fi, "%d", &model_type);
	fclose(fi);

	switch(model_type) {
	case 0 : writeEstimatedParameters<SingleModel>(modelF, imdName); break;
	case 1 : writeEstimatedParameters<SingleQModel>(modelF, imdName); break;
	case 2 : writeEstimatedParameters<PairedEndModel>(modelF, imdName); break;
	case 3 : writeEstimatedParameters<PairedEndQModel>(modelF, imdName); break;
	}

	return 0;
}
