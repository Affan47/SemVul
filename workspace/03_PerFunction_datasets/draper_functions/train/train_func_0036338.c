camlidl_abstract0_ap_abstract0_add_dimensions(
	value _v_man,
	value _v_a,
	value _v_dimchange,
	value _v_project)
{
  ap_manager_ptr man;
  ap_abstract0_ptr a;
  ap_dimchange_t dimchange;
  int project;
  ap_abstract0_ptr _res;
  value _vres;

  struct camlidl_ctx_struct _ctxs = { CAMLIDL_TRANSIENT, NULL };
  camlidl_ctx _ctx = &_ctxs;
  camlidl_ml2c_manager_ap_manager_ptr(_v_man, &man, _ctx);
  camlidl_ml2c_abstract0_ap_abstract0_ptr(_v_a, &a, _ctx);
  camlidl_ml2c_dim_ap_dimchange_t(_v_dimchange, &dimchange, _ctx);
  project = Int_val(_v_project);

_res = ap_abstract0_add_dimensions(man,false,a,&dimchange, project);ap_dimchange_clear(&dimchange);

  _vres = camlidl_c2ml_abstract0_ap_abstract0_ptr(&_res, _ctx);
  camlidl_free(_ctx);

if (man->result.exn!=AP_EXC_NONE) camlidl_apron_manager_check_exception(man,_ctx);

  return _vres;
}
