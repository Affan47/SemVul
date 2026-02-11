expr_has_nonpth(struct expr_t *cndx, word32 *badop)
{
 struct opinfo_t *opip;

 *badop = UNDEF;
 if (__isleaf(cndx)) return(FALSE);
 opip = &(__opinfo[cndx->optyp]);
 if (!opip->pthexpop)
  {
   *badop = cndx->optyp;
   return(TRUE);
  }

 if (cndx->lu.x != NULL)
  {
   if (expr_has_nonpth(cndx->lu.x, badop)) return(TRUE);
  }
 if (cndx->ru.x != NULL)
  {
   if (expr_has_nonpth(cndx->ru.x, badop)) return(TRUE);
  }
 return(FALSE);
}
