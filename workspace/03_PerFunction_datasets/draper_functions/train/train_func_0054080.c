uvlib_write_block(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj v_scm;
  ScmUVector* v;
  ScmObj port_scm;
  ScmPort* port;
  ScmObj start_scm;
  int start;
  ScmObj end_scm;
  int end;
  ScmObj endian_scm;
  ScmSymbol* endian;
  ScmObj SCM_SUBRARGS[9];
  int SCM_i;
  SCM_ENTER_SUBR("write-block");
  if (SCM_ARGCNT >= 6
      && !SCM_NULLP(SCM_ARGREF(SCM_ARGCNT-1)))
    Scm_Error("too many arguments: up to 5 is expected, %d given.", SCM_ARGCNT + Scm_Length(SCM_ARGREF(SCM_ARGCNT-1)) - 1);
  for (SCM_i=0; SCM_i<9; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  v_scm = SCM_SUBRARGS[0];
  if (!SCM_UVECTORP(v_scm)) Scm_Error("uniform vector required, but got %S", v_scm);
  v = SCM_UVECTOR(v_scm);
  if (SCM_ARGCNT > 1+1) {
    port_scm = SCM_SUBRARGS[1];
  } else {
    port_scm = SCM_OBJ(SCM_CUROUT);
  }
  if (!SCM_OPORTP(port_scm)) Scm_Error("output port required, but got %S", port_scm);
  port = SCM_PORT(port_scm);
  if (SCM_ARGCNT > 2+1) {
    start_scm = SCM_SUBRARGS[2];
  } else {
    start_scm = SCM_MAKE_INT(0);
  }
  if (!SCM_INTP(start_scm)) Scm_Error("small integer required, but got %S", start_scm);
  start = SCM_INT_VALUE(start_scm);
  if (SCM_ARGCNT > 3+1) {
    end_scm = SCM_SUBRARGS[3];
  } else {
    end_scm = SCM_MAKE_INT(-1);
  }
  if (!SCM_INTP(end_scm)) Scm_Error("small integer required, but got %S", end_scm);
  end = SCM_INT_VALUE(end_scm);
  if (SCM_ARGCNT > 4+1) {
    endian_scm = SCM_SUBRARGS[4];
  } else {
    endian_scm = SCM_FALSE;
  }
  if (!SCM_MAYBE_P(SCM_SYMBOLP, endian_scm)) Scm_Error("symbol or #f required, but got %S", endian_scm);
  endian = SCM_MAYBE(SCM_SYMBOL, endian_scm);
  {
{
ScmObj SCM_RESULT;
SCM_RESULT=(Scm_WriteBlock(v,port,start,end,endian));
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
