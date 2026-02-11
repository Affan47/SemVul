conv_matches (MatchTypeRef type) {
  static DString any ("%");


  if (!_name.str ().empty ())
    return _name.str () == any;


  if (_oper == OP_ANY)
    return true;


  return !type.is_undefined () && !_conv_type.is_undefined () &&
    _conv_type.matches (type);
}
