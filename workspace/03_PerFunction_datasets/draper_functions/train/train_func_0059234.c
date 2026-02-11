libstrstring_pointer_substring(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj sp_scm;
  ScmStringPointer* sp;
  ScmObj after_scm = SCM_FALSE;
  ScmObj after;
  ScmObj SCM_SUBRARGS[1];
  ScmObj SCM_OPTARGS = SCM_ARGREF(SCM_ARGCNT-1);
  int SCM_i;
  SCM_ENTER_SUBR("string-pointer-substring");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  sp_scm = SCM_SUBRARGS[0];
  if (!SCM_STRING_POINTERP(sp_scm)) Scm_Error("string pointer required, but got %S", sp_scm);
  sp = SCM_STRING_POINTER(sp_scm);
  if (Scm_Length(SCM_OPTARGS) % 2)
    Scm_Error("keyword list not even: %S", SCM_OPTARGS);
  while (!SCM_NULLP(SCM_OPTARGS)) {
    if (SCM_EQ(SCM_CAR(SCM_OPTARGS), scm__rc.d1123[255])) {
      after_scm = SCM_CADR(SCM_OPTARGS);
    }
    else Scm_Warn("unknown keyword %S", SCM_CAR(SCM_OPTARGS));
    SCM_OPTARGS = SCM_CDDR(SCM_OPTARGS);
  }
  after = (after_scm);
  {
{
ScmObj SCM_RESULT;

#line 322 "libstr.scm"
SCM_RESULT=(Scm_StringPointerSubstring(sp,!(SCM_FALSEP(after))));
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
