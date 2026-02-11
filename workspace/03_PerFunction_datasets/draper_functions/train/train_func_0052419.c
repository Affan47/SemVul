copy_mod(struct mod_t *omdp, char *newnam)
{
 struct sy_t *syp;

 __oinst_mod = omdp;
 __inst_mod = (struct mod_t *) __my_malloc(sizeof(struct mod_t));


 *__inst_mod = *omdp;

 __inst_mod->msplit = TRUE;
 __oinst_mod->mhassplit = TRUE;


 if ((syp = __add_modsym(newnam)) == NULL)
  {

   __misc_gfterr(__FILE__, __LINE__, omdp->msym->syfnam_ind,
    omdp->msym->sylin_cnt);
  }


 syp->sydecl = TRUE;
 syp->el.emdp = __inst_mod;
 syp->syfnam_ind = __oinst_mod->msym->syfnam_ind;
 syp->sylin_cnt = __oinst_mod->msym->sylin_cnt;

 __inst_mod->msym = syp;


 if (__oinst_mod->mspltmst != NULL) __misc_terr(__FILE__, __LINE__);


 (__oinst_mod->flatinum)--;

 if (__oinst_mod->flatinum == 1) __oinst_mod->minstnum = 1;
 __inst_mod->minstnum = 1;
 __inst_mod->flatinum = 1;


 if (__oinst_mod->mspltmst != NULL)
  __inst_mod->mspltmst = __oinst_mod->mspltmst;
 else __inst_mod->mspltmst = __oinst_mod;


 __inst_mod->mnxt = NULL;

 copy_modsymtabs();


 copy_mgrefs();


 __inst_mod->mdfps = NULL;


 copy_wires(__oinst_mod->msymtab);
 copy_modports();
 __inst_mod->mprms = copy_params(__oinst_mod->mprms, __oinst_mod->mprmnum,
  MODULE);


 __inst_mod->mlocprms = copy_params(__oinst_mod->mlocprms,
  __oinst_mod->mlocprmnum, MODULE);

 if (__oinst_mod->mdfps != NULL) copy_defparams();
 if (__oinst_mod->mattrs != NULL)
  __inst_mod->mattrs = copy_attrs(__oinst_mod->mattrs);
 if (__oinst_mod->mvarinits != NULL)
  __inst_mod->mvarinits = copy_varinits(__oinst_mod->mvarinits);

 copy_insts();
 copy_miarr();

 copy_gates();
 copy_mgarr();

 copy_contas();
 copy_mdtasks();

 __inst_mod->ialst = copy_ialst(__oinst_mod->ialst);
 if (__oinst_mod->mspfy != NULL) copy_specify();
}
