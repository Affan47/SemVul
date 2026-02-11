camlidl_manager_ap_manager_get_funopt(
	value _v_man,
	value _v_funid)
{
  ap_manager_ptr man;
  ap_funid_t funid;
  struct ap_funopt_t _res;
  value _vres;

  struct camlidl_ctx_struct _ctxs = { CAMLIDL_TRANSIENT, NULL };
  camlidl_ctx _ctx = &_ctxs;
  camlidl_ml2c_manager_ap_manager_ptr(_v_man, &man, _ctx);
  camlidl_ml2c_manager_ap_funid_t(_v_funid, &funid, _ctx);

if (funid >= AP_FUNID_SIZE) invalid_argument("Manager.get.funopt <funid>: <funid> should be different from Funid_change_environment and Funid_rename_array (no option for remaining identifiers)");
_res = ap_manager_get_funopt(man,funid);


  _vres = camlidl_c2ml_manager_struct_ap_funopt_t(&_res, _ctx);
  camlidl_free(_ctx);
  return _vres;
}
