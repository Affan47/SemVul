uvlib_u32vector_fillX(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj v_scm;
  ScmU32Vector* v;
  ScmObj val_scm;
  ScmObj val;
  ScmObj start_scm;
  int start;
  ScmObj end_scm;
  int end;
  ScmObj SCM_SUBRARGS[6];
  int SCM_i;
  SCM_ENTER_SUBR("u32vector-fill!");
  if (SCM_ARGCNT >= 5
      && !SCM_NULLP(SCM_ARGREF(SCM_ARGCNT-1)))
    Scm_Error("too many arguments: up to 4 is expected, %d given.", SCM_ARGCNT + Scm_Length(SCM_ARGREF(SCM_ARGCNT-1)) - 1);
  for (SCM_i=0; SCM_i<6; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  v_scm = SCM_SUBRARGS[0];
  if (!SCM_U32VECTORP(v_scm)) Scm_Error("u32vector required, but got %S", v_scm);
  v = SCM_U32VECTOR(v_scm);
  val_scm = SCM_SUBRARGS[1];
  val = (val_scm);
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
  {
{
ScmObj SCM_RESULT;

#line 524 "uvlib.stub"
{ScmUInt32 filler;
u32unboxer(filler,val);
SCM_RESULT=(Scm_U32VectorFill(v,filler,start,end));}
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
