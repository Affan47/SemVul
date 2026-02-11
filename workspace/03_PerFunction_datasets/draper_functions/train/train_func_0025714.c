tf_movepvc_flag(int32 nparam)
{
 register int32 i, ii;
 byte oldpvc;
 int32 rv;
 struct tfarg_t *tfap;

 if (__tfrec == NULL) return(bad_notfcontext_err("tf_movepvc_flag"));
 ii = __inum;
 rv = 0;
 if (nparam == -1)
  {

   for (i = 1; i < __tfrec->tfanump1; i++)
    {
     tfap = &(__tfrec->tfargs[i]);
     if ((oldpvc = tfap->old_pvc_flgs[ii]) != 0) rv = 1;
     tfap->old_pvc_flgs[ii] = 0;
     tfap->sav_pvc_flgs[ii] = oldpvc;
    }
   return(rv);
  }
 tfap = &(__tfrec->tfargs[nparam]);
 if ((oldpvc = tfap->old_pvc_flgs[ii]) != 0) rv = 1;
 tfap->old_pvc_flgs[ii] = 0;
 tfap->sav_pvc_flgs[ii] = oldpvc;
 return(rv);
}
