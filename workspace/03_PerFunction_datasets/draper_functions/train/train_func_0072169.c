lUndumpObject(FILE *fp)
{
   lListElem *ep;
   lDescr *dp = NULL;

   DENTER(CULL_LAYER, "lUndumpObject");

   if (!fp) {
      LERROR(LEFILENULL);
      DEXIT;
      return NULL;
   }

   if (fGetBra(fp)) {
      printf("bra is missing\n");
      LERROR(LESYNTAX);
      DEXIT;
      return NULL;
   }


   if ((dp = lUndumpDescr(fp)) == NULL) {
      LERROR(LEFGETDESCR);
      DEXIT;
      return NULL;
   }

   if (lCountDescr(dp) <= 0) {
      LERROR(LECOUNTDESCR);
      free(dp);
      DEXIT;
      return NULL;
   }

   if ((ep = lUndumpElemFp(fp, dp)) == NULL) {
      LERROR(LEUNDUMPELEM);
      free(dp);
      DEXIT;
      return NULL;
   }

   free(dp);


   if (fGetKet(fp)) {
      lFreeElem(&ep);
      printf("ket is missing\n");
      LERROR(LESYNTAX);
      DEXIT;
      return NULL;
   }

   DEXIT;
   return ep;
}
