string_scan_mode(ScmObj mode){{
#line 131 "libstr.scm"
{int rmode=0;
if (
SCM_EQ(mode,scm__rc.d1123[15])){rmode=(SCM_STRING_SCAN_INDEX);}else if(
SCM_EQ(mode,scm__rc.d1123[14])){rmode=(SCM_STRING_SCAN_BEFORE);}else if(
SCM_EQ(mode,scm__rc.d1123[13])){rmode=(SCM_STRING_SCAN_AFTER);}else if(
SCM_EQ(mode,scm__rc.d1123[12])){rmode=(SCM_STRING_SCAN_BEFORE2);}else if(
SCM_EQ(mode,scm__rc.d1123[11])){rmode=(SCM_STRING_SCAN_AFTER2);}else if(
SCM_EQ(mode,scm__rc.d1123[10])){rmode=(SCM_STRING_SCAN_BOTH);} else {
Scm_Error("bad value in mode argumet: %S, must be one of 'index, 'before, 'after, 'before*, 'after* or 'both.",mode);}
#line 141 "libstr.scm"
return (rmode);}}}
