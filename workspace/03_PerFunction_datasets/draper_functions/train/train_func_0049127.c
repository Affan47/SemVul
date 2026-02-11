resample_input_eos (ResampleState * r)
{
  RESAMPLE_DEBUG ("EOS");
  resample_input_pushthrough (r);
  r->eos = 1;
}
