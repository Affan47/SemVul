util__queuequeue_emptyP(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj q_scm;
  Queue* q;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("queue-empty?");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  q_scm = SCM_SUBRARGS[0];
  if (!QP(q_scm)) Scm_Error("queue required, but got %S", q_scm);
  q = Q(q_scm);
  {
{
int SCM_RESULT;

#line 301 "./queue.scm"
if (MTQP(q)){
{int r=FALSE;
{SCM_INTERNAL_MUTEX_SAFE_LOCK_BEGIN(MTQ_MUTEX(q));while((SCM_VMP(MTQ_LOCKER(q)))&&(!(((SCM_VM(MTQ_LOCKER(q)))->state)==(SCM_VM_TERMINATED)))){SCM_INTERNAL_COND_WAIT(MTQ_CV(q,lockWait),MTQ_MUTEX(q));}r=(Q_EMPTY_P(q));SCM_INTERNAL_MUTEX_SAFE_LOCK_END();}
SCM_RESULT=(r);}} else {
SCM_RESULT=(Q_EMPTY_P(q));}
SCM_RETURN(SCM_MAKE_BOOL(SCM_RESULT));
}
  }
}
