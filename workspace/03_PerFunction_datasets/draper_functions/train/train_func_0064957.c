param_name(int i, int j)const
{
  if (j == 0) {
    return param_name(i);
  }else if (j == 1) {
    switch (MODEL_BUILT_IN_DIODE::param_count() - 1 - i) {
    case 0:  return "";
    case 1:  return "";
    case 2:  return "";
    case 3:  return "";
    case 4:  return "";
    case 5:  return "";
    case 6:  return "";
    case 7:  return "vj";
    case 8:  return "m";
    case 9:  return "eg";
    case 10:  return "";
    case 11:  return "";
    case 12:  return "";
    case 13:  return "";
    case 14:  return "";
    case 15:  return "";
    case 16:  return "cjs";
    case 17:  return "pbs";
    case 18:  return "mjs";
    case 19:  return "gp";
    case 20:  return "";
    case 21:  return "";
    default: return "";
    }
  }else{
    return "";
  }
}
