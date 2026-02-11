set_param_by_index(int i, std::string& value, int offset)
{
  switch (MODEL_LOGIC::param_count() - 1 - i) {
  case 0: delay = value; break;
  case 1: vmax = value; break;
  case 2: vmin = value; break;
  case 3: unknown = value; break;
  case 4: rise = value; break;
  case 5: fall = value; break;
  case 6: rs = value; break;
  case 7: rw = value; break;
  case 8: th1 = value; break;
  case 9: th0 = value; break;
  case 10: mr = value; break;
  case 11: mf = value; break;
  case 12: over = value; break;
  default: MODEL_CARD::set_param_by_index(i, value, offset); break;
  }
}
