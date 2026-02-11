camlidl_abstract0_ap_abstract0_bottom(
	value _v_man,
	value _v_v1,
	value _v_v2)
{
  ap_manager_ptr man;
  int v1;
  int v2;
  ap_abstract0_ptr _res;
  value _vres;

  struct camlidl_ctx_struct _ctxs = { CAMLIDL_TRANSIENT, NULL };
  camlidl_ctx _ctx = &_ctxs;
  camlidl_ml2c_manager_ap_manager_ptr(_v_man, &man, _ctx);
  v1 = Int_val(_v_v1);
  v2 = Int_val(_v_v2);
  _res = ap_abstract0_bottom(man, v1, v2);
  _vres = camlidl_c2ml_abstract0_ap_abstract0_ptr(&_res, _ctx);
  camlidl_free(_ctx);

if (man->result.exn!=AP_EXC_NONE) camlidl_apron_manager_check_exception(man,_ctx);

  return _vres;
}
