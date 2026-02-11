iface_init_function(void* g_iface, void*)
{
  BaseClassType *const klass = static_cast<BaseClassType*>(g_iface);


  g_assert(klass != 0);

  klass->set_run_attributes = &set_run_attributes_vfunc_callback;
  klass->set_text_contents = &set_text_contents_vfunc_callback;
  klass->insert_text = &insert_text_vfunc_callback;
  klass->copy_text = &copy_text_vfunc_callback;
  klass->cut_text = &cut_text_vfunc_callback;
  klass->delete_text = &delete_text_vfunc_callback;
  klass->paste_text = &paste_text_vfunc_callback;

}
