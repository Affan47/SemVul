addphfig(const char *name)
{
phfig_list *ptfig;
char *figname;

   figname = namealloc(name);

   if (TRACE_MODE == 'Y')
      (void)fprintf(stdout, "--- mbk --- addphfig  : %s\n", figname);


   for (ptfig = HEAD_PHFIG; ptfig; ptfig = ptfig->NEXT)
      if (ptfig->NAME == figname)
         break;

   if (ptfig != NULL) {
      (void)fflush(stdout);
      (void)fprintf(stderr, "\n*** mbk error *** illegal addphfig\n");
      (void)fprintf(stderr, "figure %s already exists\n", figname);
      EXIT(1);
   }
   ptfig = (phfig_list *)mbkalloc(sizeof(phfig_list));
   ptfig->MODE       = 'A';
   ptfig->NAME       = figname;
   ptfig->MODELCHAIN = NULL;
   ptfig->PHSEG      = NULL;
   ptfig->PHCON      = NULL;
   ptfig->PHINS      = NULL;
   ptfig->PHVIA      = NULL;
   ptfig->PHREF      = NULL;
   ptfig->XAB1       = 0;
   ptfig->YAB1       = 0;
   ptfig->XAB2       = 0;
   ptfig->YAB2       = 0;
   ptfig->USER       = NULL;
   ptfig->NEXT       = HEAD_PHFIG;
   HEAD_PHFIG = ptfig;

   return ptfig;
}
