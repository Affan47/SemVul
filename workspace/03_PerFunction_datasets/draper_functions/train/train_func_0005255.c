iodeclstrprop_vpiget(struct h_t *hp, int32 prop)
{
 struct hrec_t *hrp;

 hrp = hp->hrec;
 switch (prop) {
  case vpiName:
   if (hrp->htyp2 == vpiUdpDefn)
    {

     if (hrp->hu.hmpp->mpsnam == NULL) __arg_terr(__FILE__, __LINE__);

     strcpy(__wrk_vpiget_str, hrp->hu.hmpp->mpsnam);
    }
   else strcpy(__wrk_vpiget_str, hrp->hu.hnp->nsym->synam);
   break;
  case vpiFile:
   if (hrp->htyp2 == vpiUdpDefn)
    strcpy(__wrk_vpiget_str, __in_fils[hrp->hu.hmpp->mpfnam_ind]);
   else strcpy(__wrk_vpiget_str, __in_fils[hrp->hu.hnp->nsym->syfnam_ind]);
   break;
  default: __notstrpropof_err(hrp->htyp, prop); return(NULL);
 }
 return(__wrk_vpiget_str);
}
