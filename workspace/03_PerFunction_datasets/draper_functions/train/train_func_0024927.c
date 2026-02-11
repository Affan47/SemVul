tf_getworkarea(void)
{
 if (__tfrec == NULL)
  {
   bad_notfcontext_err("tf_getworkarea");
   return(NULL);
  }
 return(__tfrec->savwrkarea[__inum]);
}
