setting_bool_validate_base(const struct setting *pset,
                                       const char *val, int *pint_val,
                                       struct connection *caller,
                                       char *reject_msg,
                                       size_t reject_msg_len)
{
  char buf[256];

  if (SSET_BOOL != pset->stype) {
    settings_snprintf(reject_msg, reject_msg_len,
                      _("This setting is not a boolean."));
    return FALSE;
  }

  sz_strlcpy(buf, val);
  remove_leading_trailing_spaces(buf);

  return (setting_match_prefix(pset->boolean.name, buf, pint_val,
                               reject_msg, reject_msg_len)
          && (NULL == pset->boolean.validate
              || pset->boolean.validate(0 != *pint_val, caller, reject_msg,
                                        reject_msg_len)));
}
