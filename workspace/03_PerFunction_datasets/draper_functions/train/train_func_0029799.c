getlocon(lofig_list *ptfig, const char *cname)
{
locon_list  *ptcon;
char *name = namealloc(cname);

   for (ptcon = ptfig->LOCON; ptcon; ptcon = ptcon->NEXT)
      if (ptcon->NAME == name)
   return ptcon;

   (void)fflush(stdout);
   (void)fprintf(stderr, "*** mbk error ***\n");
   (void)fprintf(stderr, "getlocon impossible :\n");
   (void)fprintf(stderr, "connector %s doesn't exist in figure %s\n",
                    name, ptfig->NAME);
   EXIT(1);
   return NULL;
}
