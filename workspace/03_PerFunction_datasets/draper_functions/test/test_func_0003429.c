cmdhelp_destroy(struct cmdhelp *pcmdhelp)
{
  if (pcmdhelp) {
    if (pcmdhelp->cmdname) {
      free(pcmdhelp->cmdname);
    }
    cmdarg_list_iterate(pcmdhelp->cmdarglist, pcmdarg) {
      cmdarg_destroy(pcmdarg);
    } cmdarg_list_iterate_end;
  }
  free(pcmdhelp);
}
