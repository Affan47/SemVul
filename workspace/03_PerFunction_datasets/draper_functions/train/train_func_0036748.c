dmp_macdef_exptab(char *dnam, struct macexp_t *mxp)
{
 int32 argno;

 __dbg_msg("+++ arg text macro %s defined - expands from:\n", dnam);
 for (argno = 1; mxp != NULL; mxp = mxp->macexpnxt, argno++)
  {
   __dbg_msg("    arg. %d: prefix [%s] insert actual %d\n",
    argno, mxp->leading_str, mxp->ins_argno);
  }
 __dbg_msg("+++ end of formal args +++\n");
}
