IS_Free (IS_dataType *is)
{
   int i;
   for (i = 0; i < 8; i++) {
      free (is->is[i]);
      is->is[i] = NULL;
      is->ns[i] = 0;
   }

   free (is->iain);
   is->iain = NULL;
   free (is->ib);
   is->ib = NULL;
   is->nd2x3 = 0;

   free (is->idat);
   is->idat = NULL;
   is->nidat = 0;

   free (is->rdat);
   is->rdat = NULL;
   is->nrdat = 0;

   free (is->ipack);
   is->ipack = NULL;
   is->ipackLen = 0;
}
