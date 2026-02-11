free_dftwaves(DFTWAVES *dftwaves)
{
   int i;

   for(i = 0; i < dftwaves->nwaves; i++){
       free(dftwaves->waves[i]->cos);
       free(dftwaves->waves[i]->sin);
       free(dftwaves->waves[i]);
   }
   free(dftwaves->waves);
   free(dftwaves);
}
