invoke_pileup_callback_fun(uint32_t tid,
			       uint32_t pos,
			       int n,
			       const bam_pileup1_t *pl,
			       void *data) {
  dSP;
  int count,i;
  fetch_callback_dataptr fcp;
  SV*  callback;
  SV*  callbackdata;
  SV*  pileup_obj;
  SV* p;
  SV** pileups;
  AV*  pileup;

  fcp          = (fetch_callback_dataptr) data;
  callback     = fcp->callback;
  callbackdata = fcp->data;


  pileup = newAV();
  av_extend(pileup,n);
  for (i=0;i<n;i++) {
    p = newSV(sizeof(bam_pileup1_t));
    sv_setref_pv(p,"Bio::DB::Bam::Pileup",(void*) &pl[i]);
    av_push(pileup,p);
  }


  ENTER;
  SAVETMPS;

  PUSHMARK(SP);
  XPUSHs(sv_2mortal(newSViv(tid)));
  XPUSHs(sv_2mortal(newSViv(pos)));
  XPUSHs(sv_2mortal(newRV_noinc((SV*)pileup)));
  XPUSHs(callbackdata);
  PUTBACK;


  count = call_sv(callback,G_SCALAR|G_DISCARD);

  FREETMPS;
  LEAVE;
}
