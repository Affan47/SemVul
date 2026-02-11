setting_enum_set(struct setting *pset, const char *val,
                      struct connection *caller, char *reject_msg,
                      size_t reject_msg_len)
{
  int int_val;

  if (!setting_is_changeable(pset, caller, reject_msg, reject_msg_len)) {
    return FALSE;
  }

  if (!setting_enum_validate_base(pset, val, &int_val, caller,
                                  reject_msg, reject_msg_len)) {
    return FALSE;
  }

  if (!set_enum_value(pset, int_val)) {
    log_error("Illegal enumerator value size %d for %s",
              pset->enumerator.store_size, val);
    return FALSE;
  }

  return TRUE;
}
