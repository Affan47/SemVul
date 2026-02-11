getlofig(const char *fname, char mode)
{
lofig_list *ptfig;
char *figname = namealloc(fname);

   for (ptfig = HEAD_LOFIG; ptfig; ptfig = ptfig->NEXT)
      if (ptfig->NAME == figname)
         break;

   if (ptfig == NULL) {
      ptfig = (lofig_list *)mbkalloc(sizeof(lofig_list));
      ptfig->NAME   = figname;
      ptfig->MODELCHAIN  = NULL;
      ptfig->LOINS  = NULL;
      ptfig->LOTRS  = NULL;
      ptfig->LOCAP  = NULL;
      ptfig->LORES  = NULL;
      ptfig->LOSELF = NULL;
      ptfig->LOCON  = NULL;
      ptfig->LOSIG  = NULL;
      ptfig->BKSIG  = NULL;
      ptfig->USER   = NULL;
      ptfig->NEXT   = HEAD_LOFIG;
      HEAD_LOFIG = ptfig;
      ptfig->MODE = mode;
      loadlofig(ptfig, figname, mode );
      return ptfig;
   }

   return ptfig;
}
