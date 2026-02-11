liblistappendX(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj list_scm;
  ScmObj list;
  ScmObj SCM_SUBRARGS[2];
  int SCM_i;
  SCM_ENTER_SUBR("append!");
  for (SCM_i=0; SCM_i<2; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  list_scm = SCM_SUBRARGS[SCM_ARGCNT-1];
  list = (list_scm);
  {
{
ScmObj SCM_RESULT;
ScmObj cp;
#line 172 "liblist.scm"
{ScmObj h=SCM_NIL;ScmObj t=SCM_NIL;
SCM_FOR_EACH(cp,list){
#line 175 "liblist.scm"
if ((!(SCM_PAIRP(SCM_CAR(cp))))&&(
SCM_NULLP(SCM_CDR(cp)))){{
if (SCM_NULLP(h)){
h=(SCM_CAR(cp));} else {
SCM_SET_CDR(t,SCM_CAR(cp));}
break;}}
SCM_APPEND(h,t,SCM_CAR(cp));}
SCM_RESULT=(h);}
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
