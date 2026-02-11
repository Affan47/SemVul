camlidl_abstract0_ap_abstract0_add_dimensions_with(
	value _v_man,
	value _v_a,
	value _v_dimchange,
	value _v_v1)
{
  ap_manager_ptr man;
  ap_abstract0_ptr a;
  ap_dimchange_t dimchange;
  int v1;
  struct camlidl_ctx_struct _ctxs = { CAMLIDL_TRANSIENT, NULL };
  camlidl_ctx _ctx = &_ctxs;
  camlidl_ml2c_manager_ap_manager_ptr(_v_man, &man, _ctx);
  camlidl_ml2c_abstract0_ap_abstract0_ptr(_v_a, &a, _ctx);
  camlidl_ml2c_dim_ap_dimchange_t(_v_dimchange, &dimchange, _ctx);
  v1 = Int_val(_v_v1);

{
ap_abstract0_t* res = ap_abstract0_add_dimensions(man,true,a,&dimchange,v1);
 ap_dimchange_clear(&dimchange);
*((ap_abstract0_ptr *) Data_custom_val(_v_a)) = res;
}

  camlidl_free(_ctx);

if (man->result.exn!=AP_EXC_NONE) camlidl_apron_manager_check_exception(man,_ctx);

  return Val_unit;
}
