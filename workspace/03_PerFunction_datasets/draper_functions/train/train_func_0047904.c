setting_default_name(const struct setting *pset, bool pretty,
                                 char *buf, size_t buf_len)
{
  fc_assert_ret_val(NULL != pset, NULL);
  fc_assert_ret_val(NULL != buf, NULL);
  fc_assert_ret_val(0 < buf_len, NULL);

  switch (pset->stype) {
  case SSET_BOOL:
    return setting_bool_to_str(pset, pset->boolean.default_value,
                               pretty, buf, buf_len);
  case SSET_INT:
    return setting_int_to_str(pset, pset->integer.default_value,
                              pretty, buf, buf_len);
  case SSET_STRING:
    return setting_str_to_str(pset, pset->string.default_value,
                              pretty, buf, buf_len);
  case SSET_ENUM:
    return setting_enum_to_str(pset, pset->enumerator.default_value,
                               pretty, buf, buf_len);
  case SSET_BITWISE:
    return setting_bitwise_to_str(pset, pset->bitwise.default_value,
                                  pretty, buf, buf_len);
  }

  log_error("%s(): Setting \"%s\" (nb %d) not handled in switch statement.",
            __FUNCTION__, setting_name(pset), setting_number(pset));
  return NULL;
}
