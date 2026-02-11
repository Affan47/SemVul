dev_type()const
{
  if (polarity == pN) {
    return "nmos1";
  }else if (polarity == pP) {
    return "pmos1";
  }else if (polarity == pN) {
    return "nmos";
  }else if (polarity == pP) {
    return "pmos";
  }else{untested();
    return MODEL_BUILT_IN_MOS123::dev_type();
  }
}
