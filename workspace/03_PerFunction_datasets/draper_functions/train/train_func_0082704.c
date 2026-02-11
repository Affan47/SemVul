confusion FCN(VA_ALIST((where,fmt0 VA_ARGS)))
VA_DCL(
CONST outer_char where[]C0("")
CONST outer_char fmt0[]C2(""))
{
outer_char fmt[200],temp[200];
VA_LIST(arg_ptr)
#if(NUM_VA_ARGS == 1)
CONST outer_char where[];
CONST outer_char fmt0[];
#endif

VA_START(arg_ptr,fmt0);

#if(NUM_VA_ARGS == 1)
where= va_arg(arg_ptr,outer_char*);
fmt0= va_arg(arg_ptr,outer_char*);
#endif


if(
nsprintf(fmt,OC("\n   At %s:  %s."),2,where,fmt0)>=(int)(200))OVERFLW("fmt","");
vsprintf((char*)temp,(CONST char*)fmt,arg_ptr);

beep(3);

return
fatal(ERR_NULL,OC("\n!!! \
I'M CONFUSED; this shouldn't happen.  PLEASE REPORT THIS!!!  "),OC(temp));
}
