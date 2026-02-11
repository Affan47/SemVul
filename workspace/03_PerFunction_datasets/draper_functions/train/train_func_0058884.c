__exec_all_compiletf_routines(void)
{
 register struct vpisystf_t *vstfp;

 for (vstfp = __vpi_sysf_hdr; vstfp != NULL; vstfp = vstfp->vpistfnxt)
  exec_vpisysfunc_compiletf(vstfp);

 for (vstfp = __vpi_syst_hdr; vstfp != NULL; vstfp = vstfp->vpistfnxt)
  exec_vpisystask_compiletf(vstfp);
}
