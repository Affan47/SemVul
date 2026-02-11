readMapFile(t_Map *ptMap, char *szMapFile)
{
  int i = 0, j = 0;
  char *szLine  = (char *) malloc(BIG_LINE_LENGTH*sizeof(char));
  FILE *ifp     = NULL;
  char *pcError = NULL, *szTemp  = NULL, *szTok = NULL;


  ifp = fopen(szMapFile, "r");

  if(ifp){

    ptMap->nU = 0;
    while(fgets(szLine, BIG_LINE_LENGTH, ifp) != NULL){
      ptMap->nU++;
    }
    fclose(ifp);

    ifp = fopen(szMapFile, "r");

    ptMap->anNM  = (int *) malloc(ptMap->nU*sizeof(int));
    ptMap->aanMap = (int **) malloc(ptMap->nU*sizeof(int *));

    if(!ptMap->anNM || !ptMap->aanMap)
      goto memoryError;

    for(i = 0; i < ptMap->nU; i++){
      fgets(szLine, BIG_LINE_LENGTH, ifp);

      szTok = strtok(szLine, DELIM2);

      for(j = 0; j < 3; j++){
	szTok = strtok(NULL, DELIM2);
      }

      ptMap->anNM[i] = strtol(szTok,&pcError, 10);

      ptMap->aanMap[i] = (int *) malloc(ptMap->anNM[i]*sizeof(int));
      if(!ptMap->aanMap[i])
	goto memoryError;

      for(j = 0; j < ptMap->anNM[i]; j++){
	szTok = strtok(NULL, DELIM2);

	ptMap->aanMap[i][j] = strtol(szTok,&pcError, 10);
      }

    }


    fclose(ifp);
  }
  else{
    goto fileError;
  }

  free(szLine);

  return;

 fileError:
  fprintf(stderr, "Failed to open map file\n", szMapFile);
  exit(EXIT_FAILURE);
 memoryError:
  fprintf(stderr, "Failed to allocate memory\n");
  exit(EXIT_FAILURE);
}
