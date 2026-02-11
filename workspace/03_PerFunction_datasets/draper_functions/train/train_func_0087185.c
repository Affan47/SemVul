formatOutput(MSString& str_)
{
  static const char blank[]={" "};
  A outStr = itemValue(selectedItem());
  str_ = (Ct==outStr->t) ? (char *)outStr->p : blank;
  return str_;
}
