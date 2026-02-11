caml_extunix_ssi_signo_sys(value vssi)
{
  CAMLparam1(vssi);
  struct signalfd_siginfo *ssi = (void *)(Data_custom_val(vssi));
  CAMLreturn(Val_int(caml_rev_convert_signal_number(ssi->ssi_signo)));
}
