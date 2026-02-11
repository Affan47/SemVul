ocaml_snd_pcm_get_params(value handle)
{
  CAMLparam1(handle);
  CAMLlocal1(ans);

  ans = create_hw_params();
  check_for_err(snd_pcm_hw_params_any(Pcm_handle_val(handle), Hw_params_val(ans)));

  CAMLreturn(ans);
}
