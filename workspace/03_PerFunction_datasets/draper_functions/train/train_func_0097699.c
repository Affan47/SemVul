librxrxmatch_num_matches(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj match_scm;
  ScmObj match;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("rxmatch-num-matches");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  match_scm = SCM_SUBRARGS[0];
  match = (match_scm);
  {
{
ScmObj SCM_RESULT;

#line 91 "librx.scm"
if (SCM_FALSEP(match)){
SCM_RESULT=(SCM_MAKE_INT(0));} else {
if (SCM_FALSEP(match)){SCM_RESULT=(SCM_FALSE);}else if(SCM_REGMATCHP(match)){SCM_RESULT=(SCM_MAKE_INT((SCM_REGMATCH(match))->numMatches));} else {SCM_TYPE_ERROR(match,"regmatch object or #f");SCM_RESULT=(SCM_UNDEFINED);}}
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
