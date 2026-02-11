util__queue_25qhead(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj q_scm;
  Queue* q;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("%qhead");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  q_scm = SCM_SUBRARGS[0];
  if (!QP(q_scm)) Scm_Error("queue required, but got %S", q_scm);
  q = Q(q_scm);
  {
{
ScmObj SCM_RESULT;

#line 340 "./queue.scm"
SCM_RESULT=(Q_HEAD(q));
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
