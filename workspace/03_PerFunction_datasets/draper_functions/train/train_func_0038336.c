get_syntax_plugin_by_ftype (gpointer key, gpointer value, gpointer user_data){
  Plugin *plug= PLUGIN(value);
  if (get_plugin_syntax_type(plug)==GPOINTER_TO_INT (user_data)) return TRUE;
  return FALSE;
}
