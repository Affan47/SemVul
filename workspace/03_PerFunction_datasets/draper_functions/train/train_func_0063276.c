do_tr()
{
  bool isconverged = true;
  if (OPT::bypass) {
    for (iterator ci=begin(); ci!=end(); ++ci) {
      trace_func_comp();
      if ((**ci).tr_needs_eval()) {
	isconverged &= (**ci).do_tr();
      }else{
      }
    }
  }else{
    for (iterator ci=begin(); ci!=end(); ++ci) {
      trace_func_comp();
      isconverged &= (**ci).do_tr();
    }
  }
  return isconverged;
}
