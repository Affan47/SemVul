Dddmp_cuddBddStoreCnf (
  DdManager *ddMgr              ,
  DdNode *f                     ,
  Dddmp_DecompCnfStoreType mode ,
  int noHeader                  ,
  char **varNames               ,
  int *bddIds                   ,
  int *bddAuxIds                ,
  int *cnfIds                   ,
  int idInitial                 ,
  int edgeInTh                  ,
  int pathLengthTh              ,
  char *fname                   ,
  FILE *fp                      ,
  int *clauseNPtr               ,
  int *varNewNPtr
  )
{
  int retValue;
  DdNode *tmpArray[1];

  tmpArray[0] = f;

  retValue = Dddmp_cuddBddArrayStoreCnf (ddMgr, tmpArray, 1, mode,
    noHeader, varNames, bddIds, bddAuxIds, cnfIds, idInitial, edgeInTh,
    pathLengthTh, fname, fp, clauseNPtr, varNewNPtr);

  Dddmp_CheckAndReturn (retValue==DDDMP_FAILURE, "Failure.");

  return (DDDMP_SUCCESS);
}
