setting_by_name(const char *name)
{
  fc_assert_ret_val(name, NULL);

  settings_iterate(SSET_ALL, pset) {
    if (0 == strcmp(name, pset->name)) {
      return pset;
    }
  } settings_iterate_end;
  return NULL;
}
