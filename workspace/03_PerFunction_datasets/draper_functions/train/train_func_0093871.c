libvecvector_ref(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj vec_scm;
  ScmVector* vec;
  ScmObj k_scm;
  ScmObj k;
  ScmObj fallback_scm;
  ScmObj fallback;
  ScmObj SCM_SUBRARGS[4];
  int SCM_i;
  SCM_ENTER_SUBR("vector-ref");
  if (SCM_ARGCNT >= 4
      && !SCM_NULLP(SCM_ARGREF(SCM_ARGCNT-1)))
    Scm_Error("too many arguments: up to 3 is expected, %d given.", SCM_ARGCNT + Scm_Length(SCM_ARGREF(SCM_ARGCNT-1)) - 1);
  for (SCM_i=0; SCM_i<4; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  vec_scm = SCM_SUBRARGS[0];
  if (!SCM_VECTORP(vec_scm)) Scm_Error("vector required, but got %S", vec_scm);
  vec = SCM_VECTOR(vec_scm);
  k_scm = SCM_SUBRARGS[1];
  if (!SCM_INTEGERP(k_scm)) Scm_Error("exact integer required, but got %S", k_scm);
  k = (k_scm);
  if (SCM_ARGCNT > 2+1) {
    fallback_scm = SCM_SUBRARGS[2];
  } else {
    fallback_scm = SCM_UNBOUND;
  }
  fallback = (fallback_scm);
  {
{
ScmObj SCM_RESULT;

#line 59 "libvec.scm"
if (((SCM_BIGNUMP(k))||(
(SCM_INT_VALUE(k))<(0)))||(
(SCM_INT_VALUE(k))>=(SCM_VECTOR_SIZE(vec)))){
if (SCM_UNBOUNDP(fallback)){{
Scm_Error("vector-ref index out of range: %S",k);}}
SCM_RESULT=(fallback);} else {
SCM_RESULT=(SCM_VECTOR_ELEMENT(vec,SCM_INT_VALUE(k)));}
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
