desired_settable_option_update(const char *op_name,
                                    const char *op_value,
                                    bool allow_replace)
{
  fc_assert_ret(NULL != settable_options_hash);

  if (allow_replace) {
    settable_options_hash_replace(settable_options_hash, op_name, op_value);
  } else {
    settable_options_hash_insert(settable_options_hash, op_name, op_value);
  }
}
