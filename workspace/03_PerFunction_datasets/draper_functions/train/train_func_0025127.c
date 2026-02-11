camlidl_abstract1_ap_abstract1_fold_with(
	value _v_man,
	value _v_a,
	value _v_v1)
{
  ap_manager_ptr man;
  struct ap_abstract1_t *a;
  ap_var_t *v1;
  int v2;
  struct ap_abstract1_t _c1;
  mlsize_t _c2;
  mlsize_t _c3;
  value _v4;
  struct camlidl_ctx_struct _ctxs = { CAMLIDL_TRANSIENT, NULL };
  camlidl_ctx _ctx = &_ctxs;
  camlidl_ml2c_manager_ap_manager_ptr(_v_man, &man, _ctx);
  a = &_c1;
  camlidl_ml2c_abstract1_struct_ap_abstract1_t(_v_a, &_c1, _ctx);
  _c2 = Wosize_val(_v_v1);
  v1 = camlidl_malloc(_c2 * sizeof(ap_var_t ), _ctx);
  for (_c3 = 0; _c3 < _c2; _c3++) {
    _v4 = Field(_v_v1, _c3);
    camlidl_ml2c_var_ap_var_t(_v4, &v1[_c3], _ctx);
  }
  v2 = _c2;

{
ap_environment_t* oldenv = ap_environment_copy(a->env);
		ap_abstract1_t res = ap_abstract1_fold(man,true,a,v1,v2);
  value v = Field(_v_a,0);
*((ap_abstract0_ptr *) Data_custom_val(v)) = res.abstract0;
if (res.env==oldenv){
ap_environment_free(oldenv);
}
else {
v = camlidl_apron_environment_ptr_c2ml(&res.env);
Store_field(_v_a,1,v);
}
}

  camlidl_free(_ctx);

if (man->result.exn!=AP_EXC_NONE) camlidl_apron_manager_check_exception(man,_ctx);

  return Val_unit;
}
