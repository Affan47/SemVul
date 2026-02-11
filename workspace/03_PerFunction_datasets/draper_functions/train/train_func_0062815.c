map_nodes()
{
  for (iterator ci=begin(); ci!=end(); ++ci) {
    trace_func_comp();
    (**ci).map_nodes();
  }
  return *this;
}
