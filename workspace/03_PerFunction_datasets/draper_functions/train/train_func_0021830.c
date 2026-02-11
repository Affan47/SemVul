camlidl_abstract0_ap_abstract0_to_box(
	value _v_man,
	value _v_a)
{
  ap_manager_ptr man;
  ap_abstract0_ptr a;
  struct ap_interval_array_t _res;
  value _vres;

  struct camlidl_ctx_struct _ctxs = { CAMLIDL_TRANSIENT, NULL };
  camlidl_ctx _ctx = &_ctxs;
  camlidl_ml2c_manager_ap_manager_ptr(_v_man, &man, _ctx);
  camlidl_ml2c_abstract0_ap_abstract0_ptr(_v_a, &a, _ctx);

{
ap_dimension_t dim;
  _res.p = ap_abstract0_to_box(man,a);
dim = ap_abstract0_dimension(man,a);
_res.size = dim.intdim + dim.realdim;
}

  _vres = camlidl_c2ml_interval_struct_ap_interval_array_t(&_res, _ctx);
  camlidl_free(_ctx);

ap_interval_array_free(_res.p, _res.size); if (man->result.exn!=AP_EXC_NONE) camlidl_apron_manager_check_exception(man,_ctx);

  return _vres;
}
