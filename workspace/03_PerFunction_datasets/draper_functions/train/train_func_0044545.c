NodeTextStoreBdd (
  DdManager *ddMgr  ,
  DdNode *f         ,
  int mode          ,
  int *supportids   ,
  char **varnames   ,
  int *outids       ,
  FILE *fp          ,
  int idf           ,
  int vf            ,
  int idT           ,
  int idE
  )
{
  int retValue = EOF;


  if (Cudd_IsConstant(f)) {

    if (f == Cudd_ReadOne(ddMgr)) {
      if ((varnames != NULL) || (outids != NULL)) {
        retValue = fprintf (fp, "%d T 1 0 0\n", idf);
      } else {
        retValue = fprintf (fp, "%d 1 0 0\n", idf);
      }

      if (retValue == EOF) {
        return (DDDMP_FAILURE);
      } else {
        return (DDDMP_SUCCESS);
      }
    }

    if (f == Cudd_ReadZero(ddMgr)) {
      if ((varnames != NULL) || (outids != NULL)) {
        retValue = fprintf (fp, "%d T 0 0 0\n", idf);
      } else {
        retValue = fprintf (fp, "%d 0 0 0\n", idf);
      }

      if (retValue == EOF) {
        return (DDDMP_FAILURE);
      } else {
        return (DDDMP_SUCCESS);
      }
    }


    Dddmp_CheckAndReturn (((varnames!=NULL)||(outids!=NULL)),
      "Error writing to file: ADD Type.");

    if (retValue == EOF) {
      return (DDDMP_FAILURE);
    } else {
      return (DDDMP_SUCCESS);
    }
  }


  if (Cudd_IsComplement (cuddE(f))) {
    idE = -idE;
  }

  if (varnames != NULL) {
    retValue = fprintf (fp, "%d %s %d %d %d\n",
       idf, varnames[vf], supportids[vf], idT, idE);

    if (retValue == EOF) {
      return (DDDMP_FAILURE);
    } else {
      return (DDDMP_SUCCESS);
    }
  }

  if (outids != NULL) {
    retValue = fprintf (fp, "%d %d %d %d %d\n",
       idf, outids[vf], supportids[vf], idT, idE);

    if (retValue == EOF) {
      return (DDDMP_FAILURE);
    } else {
      return (DDDMP_SUCCESS);
    }
    }

  retValue = fprintf (fp, "%d %d %d %d\n",
    idf, supportids[vf], idT, idE);

  if (retValue == EOF) {
    return (DDDMP_FAILURE);
  } else {
    return (DDDMP_SUCCESS);
  }
}
