genDEF_PHFIG( char  *name )
{
phfig_list *ptfig;
char *s;

   if (!CATA_LIB || !WORK_LIB)
      mbkenv();
   s = namealloc(name);
   for (ptfig = HEAD_PHFIG; ptfig; ptfig = ptfig->NEXT)
      if (ptfig->NAME == s)
         break;
   if (ptfig == NULL)
      WORK_PHFIG = addphfig(s);
   else
      WORK_PHFIG = ptfig;
   phlist = addchain(phlist, WORK_PHFIG);
}
