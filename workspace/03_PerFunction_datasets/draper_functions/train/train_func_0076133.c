netlib_inet_checksum(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj buf_scm;
  ScmUVector* buf;
  ScmObj size_scm;
  int size;
  ScmObj SCM_SUBRARGS[2];
  int SCM_i;
  SCM_ENTER_SUBR("inet-checksum");
  for (SCM_i=0; SCM_i<2; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  buf_scm = SCM_SUBRARGS[0];
  if (!SCM_UVECTORP(buf_scm)) Scm_Error("uniform vector required, but got %S", buf_scm);
  buf = SCM_UVECTOR(buf_scm);
  size_scm = SCM_SUBRARGS[1];
  if (!SCM_INTEGERP(size_scm)) Scm_Error("C integer required, but got %S", size_scm);
  size = Scm_GetInteger(size_scm);
  {
{
u_int SCM_RESULT;

#line 452 "netlib.stub"
{uint16_t* wp=((uint16_t* )(SCM_UVECTOR_ELEMENTS(buf)));u_long sum=0;uint16_t result;
#line 455 "netlib.stub"
if ((size)>(Scm_UVectorSizeInBytes(buf))){{
Scm_Error("uniform vector buffer too short: %S",buf);}}
for (; (size)>(0); (size)-=(2)){
if ((size)==(1)){{

#if WORDS_BIGENDIAN

#line 460 "netlib.stub"
(sum)+=((*(((u_char* )(wp))))<<(8));
#else

#line 461 "netlib.stub"
(sum)+=(*(((u_char* )(wp))));
#endif

#line 462 "netlib.stub"
break;}}
(sum)+=(*((wp)++));}
sum=(((sum)>>(16))+((sum)&(65535)));
(sum)+=((sum)>>(16));
result=(((uint16_t )(~(sum))));

#if !WORDS_BIGENDIAN

#line 468 "netlib.stub"
result=(((result)>>(8))|((result)<<(8)));
#endif

#line 469 "netlib.stub"
SCM_RESULT=(result);}
SCM_RETURN(Scm_MakeIntegerFromUI(SCM_RESULT));
}
  }
}
