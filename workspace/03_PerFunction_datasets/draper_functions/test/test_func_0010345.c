set_dev_type(const std::string& new_type)
{
  if (Umatch(new_type, "nmos1 ")) {
    polarity = pN;
  }else if (Umatch(new_type, "pmos1 ")) {
    polarity = pP;
  }else if (Umatch(new_type, "nmos ")) {
    polarity = pN;
  }else if (Umatch(new_type, "pmos ")) {
    polarity = pP;
  }else{
    MODEL_BUILT_IN_MOS123::set_dev_type(new_type);
  }
}
