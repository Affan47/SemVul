param_value(int i)const
{
  if (has_common()) {
    return common()->param_value(i);
  }else{
    switch (COMPONENT::param_count() - 1 - i) {
    case 0:  return value().string();
    case 1:  return _mfactor.string();
    default: return CARD::param_value(i);
    }
  }
}
