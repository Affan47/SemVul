util__queuemtqueue_max_length(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj q_scm;
  MtQueue* q;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("mtqueue-max-length");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  q_scm = SCM_SUBRARGS[0];
  if (!MTQP(q_scm)) Scm_Error("mt-queue required, but got %S", q_scm);
  q = MTQ(q_scm);
  {
{
ScmObj SCM_RESULT;

#line 323 "./queue.scm"
SCM_RESULT=((((MTQ_MAXLEN(q))>=(0))?(SCM_MAKE_INT(MTQ_MAXLEN(q))):(SCM_FALSE)));
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
