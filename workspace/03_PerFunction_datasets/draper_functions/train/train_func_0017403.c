get_pin_name(unsigned int pin_number)
{
  static string invalid("");
  if(package)
    return package->get_pin_name(pin_number);
  return invalid;

}
