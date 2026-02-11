make_pssm()
{
   struct work_pssm *pssm;
   int pos, aa;

   pssm = (struct work_pssm *) malloc(sizeof(struct work_pssm));
   if (pssm == NULL)
   {
      printf("make_pssm: OUT OF MEMORY\n");
      exit(-1);
   }
   for (pos = 0; pos < MAXWIDTH; pos++)
   {
      pssm->sum[pos] = 0.0;
      for (aa=0; aa < AASALL; aa++)
         pssm->value[pos][aa] = 0.0;
   }
   return(pssm);

}
