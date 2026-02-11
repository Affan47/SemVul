ml_gdome_evntl_create(value callback)
{
  CAMLparam1(callback);

  static struct custom_operations ops = {
    "http://gmetadom.sourceforge.net/gdome_caml/events/EventListener",
    ml_gdome_evntl_finalize,
    custom_compare_default,
    custom_hash_default,
    custom_serialize_default,
    custom_deserialize_default
  };


  value* cb = g_new(value, 1);
  value v = alloc_custom(&ops, sizeof(GdomeEventListener*), 0, 1);
  GdomeEventListener* listener = *((GdomeEventListener**) Data_custom_val(v)) = gdome_evntl_aux_mkref(ml_gdome_evntl_callback, cb,
		  ml_gdome_evntl_priv_callback);
  *cb = callback;
  register_global_root(cb);

  CAMLreturn(v);
}
