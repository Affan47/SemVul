uvlib_uvector_swap_bytesX(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj v_scm;
  ScmUVector* v;
  ScmObj type_scm;
  ScmSymbol* type;
  ScmObj SCM_SUBRARGS[3];
  int SCM_i;
  SCM_ENTER_SUBR("uvector-swap-bytes!");
  if (SCM_ARGCNT >= 3
      && !SCM_NULLP(SCM_ARGREF(SCM_ARGCNT-1)))
    Scm_Error("too many arguments: up to 2 is expected, %d given.", SCM_ARGCNT + Scm_Length(SCM_ARGREF(SCM_ARGCNT-1)) - 1);
  for (SCM_i=0; SCM_i<3; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  v_scm = SCM_SUBRARGS[0];
  if (!SCM_UVECTORP(v_scm)) Scm_Error("uniform vector required, but got %S", v_scm);
  v = SCM_UVECTOR(v_scm);
  if (SCM_ARGCNT > 1+1) {
    type_scm = SCM_SUBRARGS[1];
  } else {
    type_scm = SCM_FALSE;
  }
  if (!SCM_MAYBE_P(SCM_SYMBOLP, type_scm)) Scm_Error("symbol or #f required, but got %S", type_scm);
  type = SCM_MAYBE(SCM_SYMBOL, type_scm);
  {
{
ScmObj SCM_RESULT;

#line 1429 "uvlib.stub"
{int opt=SWAPB_STD;if ((type)==(NULL)){}else if(SCM_EQ(SCM_OBJ(type),scm__rc.d1426[4])){opt=(SWAPB_ARM_LE);}else if(SCM_EQ(SCM_OBJ(type),scm__rc.d1426[3])){opt=(SWAPB_ARM_BE);} else {Scm_TypeError("type","#f or a symbol le:arm-le or be:arm-le",SCM_OBJ(type));}Scm_UVectorSwapBytesX(v,opt);}
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
