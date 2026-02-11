ocaml_snd_pcm_readn_float(value handle_, value dbuf, value ofs_, value len_)
{
  CAMLparam4(handle_, dbuf, ofs_, len_);
  int len = Int_val(len_);
  int ofs = Int_val(ofs_);
  int chans = Wosize_val(dbuf);
  snd_pcm_t *handle = Pcm_handle_val(handle_);
  float **buf;
  int c, i;
  snd_pcm_sframes_t ret;


  buf = malloc(chans * sizeof(float*));
  for(c = 0; c < chans; c++)
    buf[c] = malloc(len * sizeof(float));

  caml_enter_blocking_section();
  ret = snd_pcm_readn(handle, (void**)buf, len);
  caml_leave_blocking_section();

  for(c = 0; c < chans; c++)
  {
    for(i = 0; i < len; i++)
      Store_double_field(Field(dbuf, c), i + ofs, buf[c][i]);
    free(buf[c]);
  }
  free(buf);
  check_for_err(ret);

  CAMLreturn(Val_int(ret));
}
