ocaml_ao_stubs_close(value v_dev)
{
  CAMLparam1(v_dev);
  ao_close((ao_device*)v_dev);
  CAMLreturn(Val_unit);
}
