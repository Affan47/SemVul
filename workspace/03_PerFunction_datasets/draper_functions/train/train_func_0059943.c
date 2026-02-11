SetError(int ec,const char *e)
{
   if(ec==SEE_ERRNO && !saved_errno)
      saved_errno=errno;
   if(ec==NO_FILE && file && file[0] && !strstr(e,file))
      error.vset(e," (",file.get(),")",NULL);
   else
      error.set(e);
   error_code=ec;
}
