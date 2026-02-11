dmp_down_itree(struct itree_t *itp, int32 lev, int32 more_down)
{
 register int32 i;
 int32 ofsnum, retval;

 if (more_down == 0) { do_dmp(itp, lev); return(TRUE); }
 if ((ofsnum = itp->itip->imsym->el.emdp->minum) == 0) return(FALSE);
 for (retval= FALSE, i = 0; i < ofsnum; i++)
  {
   if (dmp_down_itree(&(itp->in_its[i]), lev, more_down - 1))
    retval = TRUE;
  }
 return(retval);
}
