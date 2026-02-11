get_gene_names(NetParameters *params) {
  FILE * genesf;
  int i = 0;
  int num_read;
  char element[128];


  params->genes = (char **) malloc(sizeof(char *) * params->numGenes);


  if (!params->quiet) {
    printf("  Opening file %s\n", params->genes_file);
  }
  genesf = fopen(params->genes_file, "r");
  if (genesf == NULL) {
    fprintf(stderr, "ERROR: cannot open file: %s\n", params->genes_file);
    exit(-1);
  }

  for (i = 0; i < params->numGenes; i++) {
    num_read = fscanf(genesf, "%s", element);
    if (num_read == 0) {
      fprintf(stderr, "ERROR: gene file has %d lines, but it should have %d\n", i, params->numGenes);
      exit(-1);
    }
    params->genes[i] = (char *) malloc(sizeof(char) * strlen(element) + 1);
    strcpy(params->genes[i], element);
  }
  fclose(genesf);
}
