writeClustersD3(t_Params *ptParams, int nN, int nM, int nK, int *anZ, short* asCentroids)
{
  char *szClustFile = (char *) malloc(MAX_LINE_LENGTH*sizeof(char));
  FILE *ofp = NULL;
  int i = 0, j = 0, s = 0;
  int*  anT = (int * ) malloc(nK*sizeof(int));

  sprintf(szClustFile, "%s_cd3%s", ptParams->szOutFileStub, FASTA_SUFFIX);
  ofp = fopen(szClustFile, "w");

  for(i = 0; i < nK; i++){
    anT[i] = 0;
  }
  for(i = 0; i < nN; i++){
    anT[anZ[i]]++;
  }

  for(i = 0; i < nK; i++){
    if(anT[i] > 0){
      fprintf(ofp, ">%s_%d_%d\n",ptParams->szOutFileStub,i, anT[i]);

      for(j = gOffSet; j < nM; j++){
	char   cBase = szFlows[j];

	for(s = 0; s < asCentroids[i*nM + j]; s++){
	  fprintf(ofp, "%c", cBase);
	}
      }
      fprintf(ofp,"\n");
    }
  }

  free(anT);
  fclose(ofp);
  free(szClustFile);
}
