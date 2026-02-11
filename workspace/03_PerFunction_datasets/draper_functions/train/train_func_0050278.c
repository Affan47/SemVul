ocaml_ao_stubs_find_driver(value v_short_name)
{
  CAMLparam0();
  int driver =
    ao_driver_id(String_val(v_short_name));

  if (driver < 0) {
    my_failwith("Could not find driver for name \"%s\"", String_val(v_short_name));
  };

  CAMLreturn(Val_int(driver));
}
