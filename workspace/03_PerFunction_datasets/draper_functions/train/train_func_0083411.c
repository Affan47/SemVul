xiph_get_field(const FXchar * field,FXString & value) {
  FXASSERT(field);
  FXASSERT(xiph);
  if (xiph->contains(field))
    value=xiph->fieldListMap()[field].front().toCString(true);
  else
    value.clear();
  }
