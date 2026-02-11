set_enabled(int en)
{

  if (enable_handler) {
    en = (*enable_handler)(this, en);
  }
  bx_param_c::set_enabled(en);
  update_dependents();
}
