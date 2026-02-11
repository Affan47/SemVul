readData(t_Data *ptData, t_Params *ptParams)
{
  FILE *ifp = NULL;
  char szLine[MAX_LINE_LENGTH];
  int  nPos = 0, i = 0, j = 0, nM = 0, nSequences = 0;
  char *szBrk;
  char *szRet;


  ptData->nSeq    = 0;
  ptData->nMaxLen = 0;

  ifp = fopen(ptParams->szInputFile, "r");

  if(ifp){
    while(fgets(szLine, MAX_LINE_LENGTH, ifp)){
      if(szLine[0] == '>'){
	if(nPos > ptData->nMaxLen){
	  ptData->nMaxLen = nPos;
	}

	ptData->nSeq++;
	nPos = 0;
      }
      else{

	if(! ptData->nSeq)
	{
	    fprintf(stderr, "File %s does not appear to be in FASTA format.\n", ptParams->szInputFile);
	    exit(EXIT_FAILURE);
	}

	i = 0;
	while(strrchr(szSequence,szLine[i]) != NULL){
	  i++;
	  nPos++;
	}
      }
    }

    if(nPos > ptData->nMaxLen){
	ptData->nMaxLen = nPos;
    }

    fclose(ifp);
  }
  else{
    fprintf(stderr, "Can't open input file %s\n", ptParams->szInputFile);
    exit(EXIT_FAILURE);
  }

  ptData->aszID        = (char **) malloc(ptData->nSeq*sizeof(char *));

  nM = ptData->nMaxLen;
  ptData->acSequences = (char *) malloc(ptData->nSeq*nM*sizeof(char));
  ptData->anLen       = (int *)  malloc(ptData->nSeq*sizeof(int));

  ifp = fopen(ptParams->szInputFile, "r");

  if(ifp){
    while(szRet = fgets(szLine, MAX_LINE_LENGTH, ifp)){
      if(szLine[0] == '>'){
	if(nSequences > 0){
	  ptData->anLen[nSequences - 1] = nPos;
	}

	szBrk = strpbrk(szLine, " \n");
	(*szBrk) = '\0';
	ptData->aszID[nSequences] = strdup(szLine + 1);
	nPos = 0;
	nSequences++;
      }

      i = 0;
      while(szLine[i] != '\0' && strrchr(szSequence,szLine[i]) != NULL){
	ptData->acSequences[(nSequences - 1)*nM + nPos] = toupper(szLine[i]);

	nPos++; i++;
      }
    }

    ptData->anLen[nSequences - 1] = nPos;

    fclose(ifp);
  }
  else{
    fprintf(stderr, "Can't open input file %s\n", ptParams->szInputFile);
    exit(EXIT_FAILURE);
  }
}
