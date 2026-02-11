exec_prttimscale(struct expr_t *axp)
{
 struct mod_t *mdp;
 struct expr_t *ndp;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN];

 __cur_sofs = 0;
 __adds("Time scale of (");
 if (axp == NULL)
  {
   mdp = __scope_ptr->itip->imsym->el.emdp;
   __disp_itree_path(__inst_ptr, (struct task_t *) NULL);
  }
 else
  {
   ndp = axp->lu.x;
   if (ndp->optyp == GLBREF)
    { mdp = ndp->ru.grp->targmdp; __adds(ndp->ru.grp->gnam); }
   else if (ndp->lu.sy->sytyp == SYM_M)
    { mdp = ndp->lu.sy->el.emdp; __adds(mdp->msym->synam); }
   else { __case_terr(__FILE__, __LINE__);  return; }
  }
 sprintf(s1, ") is %s / %s\n",
  __to_timunitnam(s2, mdp->mtime_units),
  __to_timunitnam(s3, mdp->mtime_units + mdp->mtime_prec));
 __adds(s1);

 my_puts_(__exprline, stdout);
 __cur_sofs = 0;
}
