acc_fetch_polarity(handle path)
{
 int32 rv;
 struct h_t *hp;
 struct hrec_t *hrp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) path;
 if (!validate_acc_handle("acc_fetch_polarity", hp)) return(0);
 hrp = hp->hrec;

 if (hrp->htyp != vpiModPath)
  {
   __acc_err(1946,
    "acc_fetch_polarity: object %s does not have polarity - accModPath required",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(0);
  }

 __acc_vpi_erroff = TRUE;
 rv = vpi_get(vpiPolarity, (vpiHandle) path);


 if (__my_vpi_chk_error())
  {
   __acc_err(1959,
    "acc_fetch_polarity: unable to access polarity for object %s",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(0);
  }

 return(rv);
}
