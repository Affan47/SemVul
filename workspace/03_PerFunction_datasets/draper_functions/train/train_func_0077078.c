libobj_25make_record(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj klass_scm;
  ScmClass* klass;
  ScmObj* inits;
  int numinits;
  ScmObj rinits_scm;
  ScmObj rinits;
  ScmObj SCM_SUBRARGS[14];
  int SCM_i;
  SCM_ENTER_SUBR("%make-record");
  for (SCM_i=0; SCM_i<14; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  klass_scm = SCM_SUBRARGS[0];
  if (!SCM_CLASSP(klass_scm)) Scm_Error("class required, but got %S", klass_scm);
  klass = SCM_CLASS(klass_scm);
  inits = &SCM_SUBRARGS[1];
  numinits = SCM_ARGCNT-1-1;
  rinits_scm = SCM_SUBRARGS[SCM_ARGCNT-1];
  rinits = (rinits_scm);
  {
{
ScmObj SCM_RESULT;
ScmObj cise__1150;
#line 525 "libobj.scm"
{ScmObj obj=Scm__AllocateAndInitializeInstance(klass,inits,numinits,0);
if ((numinits)==(10)){{
{int i=10;
SCM_FOR_EACH(cise__1150,rinits) {{ScmObj init=SCM_CAR(cise__1150);Scm_InstanceSlotSet(obj,(i)++,init);}}}}}
SCM_RESULT=(obj);}
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
