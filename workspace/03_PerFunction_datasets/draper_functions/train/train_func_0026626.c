setting_changed(const struct setting *pset)
{
  switch (setting_type(pset)) {
  case SSET_BOOL:
    return (*pset->boolean.pvalue != pset->boolean.default_value);
  case SSET_INT:
    return (*pset->integer.pvalue != pset->integer.default_value);
  case SSET_STRING:
    return (0 != strcmp(pset->string.value, pset->string.default_value));
  case SSET_ENUM:
    return (read_enum_value(pset) != pset->enumerator.default_value);
  case SSET_BITWISE:
    return (*pset->bitwise.pvalue != pset->bitwise.default_value);
  }

  log_error("%s(): Setting \"%s\" (nb %d) not handled in switch statement.",
            __FUNCTION__, setting_name(pset), setting_number(pset));
  return FALSE;
}
