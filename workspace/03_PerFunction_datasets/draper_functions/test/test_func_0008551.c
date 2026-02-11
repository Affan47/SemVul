fnd_tskfunc_inscope(char *ncmp,
 struct symtab_t *scope_sytp)
{
 struct symtab_t *sytp;
 struct sy_t *match_syp;

 for (sytp = scope_sytp->sytofs; sytp != NULL; sytp = sytp->sytsib)
  {
   if (strcmp(sytp->sypofsyt->synam, ncmp) == 0) return(sytp->sypofsyt);
   if ((match_syp = fnd_tskfunc_inscope(ncmp, sytp)) != NULL)
    return(match_syp);
  }
 return(NULL);
}
