camlidl_mpf_mpf__init_set_str(
	value _v_STR,
	value _v_BASE)
{
  mpf_t OUTOUTOUT; mpf_ptr OUTTOUTTOUTT = OUTOUTOUT;;
  char *STR;
  int BASE;
  value _vres;

  struct camlidl_ctx_struct _ctxs = { CAMLIDL_TRANSIENT, NULL };
  camlidl_ctx _ctx = &_ctxs;
  STR = String_val(_v_STR);
  BASE = Int_val(_v_BASE);

  {
  int n = mpf_init_set_str(OUTOUTOUT,STR,BASE);
  if (n){ mpf_clear(OUTOUTOUT); caml_invalid_argument(""); }
  }

  _vres = camlidl_c2ml_mpf_mpf_ptr(&OUTTOUTTOUTT, _ctx);
  camlidl_free(_ctx);
  return _vres;
}
