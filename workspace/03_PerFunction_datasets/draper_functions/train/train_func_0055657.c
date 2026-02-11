util__sparsesparse_vector_existsP(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj sv_scm;
  SparseVector* sv;
  ScmObj index_scm;
  u_long index;
  ScmObj SCM_SUBRARGS[2];
  int SCM_i;
  SCM_ENTER_SUBR("sparse-vector-exists?");
  for (SCM_i=0; SCM_i<2; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  sv_scm = SCM_SUBRARGS[0];
  if (!SPARSE_VECTOR_BASE_P(sv_scm)) Scm_Error("sparse vector required, but got %S", sv_scm);
  sv = SPARSE_VECTOR(sv_scm);
  index_scm = SCM_SUBRARGS[1];
  if (!SCM_UINTEGERP(index_scm)) Scm_Error("C integer required, but got %S", index_scm);
  index = Scm_GetIntegerU(index_scm);
  {
{
int SCM_RESULT;

#line 229 "./sparse.scm"
{ScmObj r=SparseVectorRef(sv,index,SCM_UNBOUND);
SCM_RESULT=(!(SCM_UNBOUNDP(r)));}
SCM_RETURN(SCM_MAKE_BOOL(SCM_RESULT));
}
  }
}
