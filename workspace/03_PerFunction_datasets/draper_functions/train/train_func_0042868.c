param_name(int i)const
{
  switch (MODEL_SEMI_BASE::param_count() - 1 - i) {
  case 0: return "narrow";
  case 1: return "defw";
  case 2: return "tc1";
  case 3: return "tc2";
  default: return MODEL_CARD::param_name(i);
  }
}
