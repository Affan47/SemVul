DddmpReadCnfClauses (
  Dddmp_Hdr_t *Hdr  ,
  int ***cnfTable   ,
  FILE *fp
  )
{
  char word[DDDMP_MAX_CNF_ROW_LENGTH];
  int i, j, var;
  int **cnfTableLocal = NULL;
  int *clause = NULL;

  cnfTableLocal = DDDMP_ALLOC (int *, Hdr->nClausesCnf);
  clause = DDDMP_ALLOC (int, 2*Hdr->nVarsCnf+1);

  for (i=0; i<Hdr->nClausesCnf; i++) {
    cnfTableLocal[i] = NULL;
  }

  for (i=0; i<=2*Hdr->nVarsCnf; i++) {
    clause[i] = 0;
  }

  i = j = 0;
  do {
    if (fscanf(fp, "%s", word)==EOF) {
      if (j>0) {

        strcpy(word,"0");
      }
      else break;
    }


    if (word[0] == 'c') {

      fgets (word, DDDMP_MAX_CNF_ROW_LENGTH-1, fp);
      break;
    }

    var = atoi (word);
    Dddmp_Assert ((var>=(-Hdr->nVarsCnf))&&(var<=Hdr->nVarsCnf),
      "Wrong num found");
    clause[j++] = var;
    if (var == 0) {
      cnfTableLocal[i] = DDDMP_ALLOC (int, j);
      while (--j >=0) {
        cnfTableLocal[i][j] = clause[j];
	}
      i++;
      j=0;
    }

  } while (!feof(fp));

  Dddmp_Assert (i==Hdr->nClausesCnf,
    "Wrong number of clauses in file");

#if DDDMP_DEBUG_CNF
  for (i=0; i<Hdr->nClausesCnf; i++) {
    fprintf (stdout, "[%4d] ", i);
    j=0;
    while ((var = cnfTableLocal[i][j++]) != 0) {
      fprintf (stdout, "%d ", var);
    }
    fprintf (stdout, "0\n");
  }
#endif

  DDDMP_FREE (clause);

  *cnfTable = cnfTableLocal;

  return (DDDMP_SUCCESS);
}
