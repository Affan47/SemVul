camlidl_linexpr0_ap_linexpr0_get_coeff(
	value _v_a,
	value _v_dim)
{
  ap_linexpr0_ptr a;
  int dim;
  struct ap_coeff_t _res;
  value _vres;

  struct camlidl_ctx_struct _ctxs = { CAMLIDL_TRANSIENT, NULL };
  camlidl_ctx _ctx = &_ctxs;
  camlidl_ml2c_linexpr0_ap_linexpr0_ptr(_v_a, &a, _ctx);
  dim = Int_val(_v_dim);


{
bool b;
ap_coeff_init(&_res,AP_COEFF_SCALAR);
if (dim<0) goto ap_linexpr0_get_coeff_exit;
b = ap_linexpr0_get_coeff(&_res,a,(ap_dim_t)dim);
   if (b){
ap_linexpr0_get_coeff_exit:
ap_coeff_clear(&_res);
caml_failwith("Linexpr0.get_coeff: out of bound dimension");
}
}

  _vres = camlidl_c2ml_coeff_struct_ap_coeff_t(&_res, _ctx);
  camlidl_free(_ctx);

ap_coeff_clear(&_res);

  return _vres;
}
