do_ac()
{
  for (iterator ci=begin(); ci!=end(); ++ci) {
    trace_func_comp();
    if (!(**ci).evaluated()) {
      (**ci).do_ac();
    }else{
    }
  }
  return *this;
}
