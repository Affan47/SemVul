caml_ml_input_int(value vchannel)
{
  CAMLparam1 (vchannel);
  struct channel * channel = Channel(vchannel);
  intnat i;

  Lock(channel);
  i = caml_getword(channel);
  Unlock(channel);
#ifdef ARCH_SIXTYFOUR
  i = (i << 32) >> 32;
#endif
  CAMLreturn (Val_long(i));
}
