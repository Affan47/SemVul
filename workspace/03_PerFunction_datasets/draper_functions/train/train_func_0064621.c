bam_fetch_fun (const bam1_t *b, void *data) {
  dSP;
  int count;

  fetch_callback_dataptr fcp;
  SV* callback;
  SV* callbackdata;
  SV* alignment_obj;
  bam1_t *b2;

  fcp          = (fetch_callback_dataptr) data;
  callback     = fcp->callback;
  callbackdata = fcp->data;


  b2 = bam_dup1(b);

  alignment_obj = sv_setref_pv(newSV(sizeof(bam1_t)),"Bio::DB::Bam::Alignment",(void*) b2);


  ENTER;
  SAVETMPS;

  PUSHMARK(SP);
  XPUSHs(sv_2mortal(alignment_obj));
  XPUSHs(callbackdata);
  PUTBACK;


  count = call_sv(callback,G_SCALAR|G_DISCARD);

  FREETMPS;
  LEAVE;

  return 1;
}
