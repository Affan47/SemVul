func_add_vpi_systf(char *fnam, int32 fnum)
{
 struct tnode_t *tnp;
 struct sy_t *syp;
 struct sysfunc_t *sfbp;

 sfbp = __alloc_sysfunc();

 sfbp->syfnam = fnam;
 sfbp->syfnum = fnum;

 sfbp->tftyp = SYSF_VPI;
 tnp = __vtfind(fnam, __syssyms);
 if (!__sym_is_new)
  {
   syp = tnp->ndp;
   __inform(2104,
    "PLI vpi systf task %s replaces predefined or veriusertf system task or function with same name",
    syp->synam);

   __vpi_err(2104, vpiNotice,
    "PLI vpi systf task %s replaces predefined or veriusertf system task or function with same name",
    syp->synam);
  }
 else
  {
   __add_sym(fnam, tnp);
   (__syssyms->numsyms)++;
   syp = tnp->ndp;
  }
 syp->sytyp = SYM_SF;
 syp->sydecl = TRUE;
 syp->el.esyftbp = sfbp;
 return(syp);
}
