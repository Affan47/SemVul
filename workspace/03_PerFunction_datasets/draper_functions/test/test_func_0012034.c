outputClusters(t_Params *ptParams, int nK, int *anZ, int nN, int nM, int* anT, t_Flows *ptFlows, char **aszLabels, int* anCentroids, t_Unique *ptUnique, char** aszIDs)
{
  FILE *ofp = NULL;
  char *szOutFile = (char *) malloc(sizeof(char)*MAX_LINE_LENGTH);
  int  s = 0, i = 0, j = 0, index = 0;

  mkdir(ptParams->szOutFileStub, S_IRWXU);

  if(!szOutFile)
    goto memoryError;

  for(i = 0; i < nK; i++){
    if(anT[i] > 0){
      sprintf(szOutFile, "%s/i_%d%s",ptParams->szOutFileStub,index, FASTA_SUFFIX);
      ofp = fopen(szOutFile, "w");
      if(ofp){
	int nUI = anCentroids[i];
	fprintf(ofp, ">%s_%d_%d\n",ptParams->szOutFileStub,index, anT[i]);

	for(j = nOffSet; j < nM; j++){
	  char   cBase = szFlows[j % 4];

	  for(s = 0; s < ptUnique->asU[nUI*nM + j]; s++){
	    fprintf(ofp, "%c", cBase);
	  }
	}

	fprintf(ofp,"\n");

	for(j = 0; j < nN; j++){
	  if(anZ[j] == i){
	    int  nLen     = 0;
	    char *szSeq   = flowToSeq(&nLen, &(ptFlows->adData[j*nM]), ptFlows->anLengths[j]);

	    writeSequenceUnaligned(ofp, aszLabels[j], szSeq, nLen);

	    free(szSeq);
	  }
	}

	fclose(ofp);
      }
      else{
	fprintf(stderr,"Can't open file %s for writing\n",szOutFile);
      }

      index++;
    }
  }

  free(szOutFile);

  return;

 memoryError:
  fprintf(stderr, "Failed allocating memory in outputClusters\n");
  fflush(stderr);
  exit(EXIT_FAILURE);
}
