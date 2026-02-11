zliblib_zstream_params_setX(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj port_scm;
  ScmPort* port;
  ScmObj compression_level_scm = SCM_FALSE;
  ScmObj compression_level;
  ScmObj strategy_scm = SCM_FALSE;
  ScmObj strategy;
  ScmObj SCM_SUBRARGS[2];
  ScmObj SCM_OPTARGS = SCM_ARGREF(SCM_ARGCNT-1);
  int SCM_i;
  SCM_ENTER_SUBR("zstream-params-set!");
  for (SCM_i=0; SCM_i<2; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  port_scm = SCM_SUBRARGS[0];
  if (!SCM_DEFLATING_PORT_P(port_scm)) Scm_Error("deflating port required, but got %S", port_scm);
  port = SCM_PORT(port_scm);
  if (Scm_Length(SCM_OPTARGS) % 2)
    Scm_Error("keyword list not even: %S", SCM_OPTARGS);
  while (!SCM_NULLP(SCM_OPTARGS)) {
    if (SCM_EQ(SCM_CAR(SCM_OPTARGS), scm__rc.d981[15])) {
      compression_level_scm = SCM_CADR(SCM_OPTARGS);
    } else
    if (SCM_EQ(SCM_CAR(SCM_OPTARGS), scm__rc.d981[16])) {
      strategy_scm = SCM_CADR(SCM_OPTARGS);
    }
    else Scm_Warn("unknown keyword %S", SCM_CAR(SCM_OPTARGS));
    SCM_OPTARGS = SCM_CDDR(SCM_OPTARGS);
  }
  compression_level = (compression_level_scm);
  strategy = (strategy_scm);
  {

#line 121 "zliblib.stub"
{ScmZlibInfo* info=SCM_PORT_ZLIB_INFO(port);z_streamp strm=
SCM_PORT_ZSTREAM(port);int lv;int st;
#line 125 "zliblib.stub"
if (
SCM_FALSEP(compression_level)){lv=((info)->level);}else if(
SCM_INTP(compression_level)){lv=(SCM_INT_VALUE(compression_level));} else {
SCM_TYPE_ERROR(compression_level,"fixnum or #f");}
if (
SCM_FALSEP(strategy)){st=((info)->strategy);}else if(
SCM_INTP(strategy)){st=(SCM_INT_VALUE(strategy));} else {
SCM_TYPE_ERROR(strategy,"fixnum or #f");}
{int r=deflateParams(strm,lv,st);
if (!((r)==(Z_OK))){{
Scm_ZlibError(r,"deflateParams failed: %s",(strm)->msg);}}}}
SCM_RETURN(SCM_UNDEFINED);
  }
}
