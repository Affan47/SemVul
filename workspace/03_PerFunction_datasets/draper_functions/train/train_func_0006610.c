update_dependents()
{
  if (dependent_list) {
    int en = (strlen(val) > 0) && (strcmp(val, "none")) && enabled;
    for (int i=0; i<dependent_list->get_size(); i++) {
      bx_param_c *param = dependent_list->get(i);
      if (param != this)
        param->set_enabled(en);
    }
  }
}
