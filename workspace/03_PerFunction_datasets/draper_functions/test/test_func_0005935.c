camlidl_abstract1_ap_abstract1_closure(
	value _v_man,
	value _v_a)
{
  ap_manager_ptr man;
  struct ap_abstract1_t *a;
  struct ap_abstract1_t _res;
  struct ap_abstract1_t _c1;
  value _vres;

  struct camlidl_ctx_struct _ctxs = { CAMLIDL_TRANSIENT, NULL };
  camlidl_ctx _ctx = &_ctxs;
  camlidl_ml2c_manager_ap_manager_ptr(_v_man, &man, _ctx);
  a = &_c1;
  camlidl_ml2c_abstract1_struct_ap_abstract1_t(_v_a, &_c1, _ctx);

_res = ap_abstract1_closure(man,false,a);

  _vres = camlidl_c2ml_abstract1_struct_ap_abstract1_t(&_res, _ctx);
  camlidl_free(_ctx);

if (man->result.exn!=AP_EXC_NONE) camlidl_apron_manager_check_exception(man,_ctx);

  return _vres;
}
