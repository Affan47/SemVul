camlidl_abstract0_ap_abstract0_meet_with(
	value _v_man,
	value _v_a1,
	value _v_a2)
{
  ap_manager_ptr man;
  ap_abstract0_ptr a1;
  ap_abstract0_ptr a2;
  struct camlidl_ctx_struct _ctxs = { CAMLIDL_TRANSIENT, NULL };
  camlidl_ctx _ctx = &_ctxs;
  camlidl_ml2c_manager_ap_manager_ptr(_v_man, &man, _ctx);
  camlidl_ml2c_abstract0_ap_abstract0_ptr(_v_a1, &a1, _ctx);
  camlidl_ml2c_abstract0_ap_abstract0_ptr(_v_a2, &a2, _ctx);

{
ap_abstract0_t* res = ap_abstract0_meet(man,true,a1,a2);
*((ap_abstract0_ptr *) Data_custom_val(_v_a1)) = res;
}

  camlidl_free(_ctx);

if (man->result.exn!=AP_EXC_NONE) camlidl_apron_manager_check_exception(man,_ctx);

  return Val_unit;
}
