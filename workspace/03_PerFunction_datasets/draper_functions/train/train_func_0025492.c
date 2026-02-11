libdicthash_table_num_entries(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj hash_scm;
  ScmHashTable* hash;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("hash-table-num-entries");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  hash_scm = SCM_SUBRARGS[0];
  if (!SCM_HASH_TABLE_P(hash_scm)) Scm_Error("hash table required, but got %S", hash_scm);
  hash = SCM_HASH_TABLE(hash_scm);
  {
{
int SCM_RESULT;

#line 138 "libdict.scm"
SCM_RESULT=(Scm_HashCoreNumEntries(SCM_HASH_TABLE_CORE(hash)));
SCM_RETURN(Scm_MakeInteger(SCM_RESULT));
}
  }
}
