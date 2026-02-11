parse_conv_id (const char *&str, MatchTypeRef &type) {

  const char *curr = str;
  FctSpec fct_spec;
  parse_decl_spec_seq (curr, type, fct_spec);
  if (error () || curr == str)
    return false;


  if (fct_spec) {
    _state = ERR_INVALID_FCT_SPEC;
    return false;
  }


  while (parse_ptr_operator (curr, type))
    if (error ()) {
      return false;
    }
  str = curr;
  return true;
}
