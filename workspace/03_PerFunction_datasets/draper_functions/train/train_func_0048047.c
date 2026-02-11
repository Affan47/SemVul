tcallstrprop_vpiget(struct h_t *hp, int32 prop)
{
 struct st_t *stp;

 stp = hp->hrec->hu.hstp;
 switch (prop) {
  case vpiFile:
   strcpy(__wrk_vpiget_str, __in_fils[stp->stfnam_ind]);
   break;
  case vpiName:
   strcpy(__wrk_vpiget_str, stp->st.stkc.tsksyx->lu.sy->synam);
   break;
  default: __notstrpropof_err(hp->hrec->htyp, prop); return(NULL);
 }
 return(__wrk_vpiget_str);
}
