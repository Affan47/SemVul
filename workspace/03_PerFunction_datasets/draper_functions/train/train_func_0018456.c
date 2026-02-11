toString() const
{
  if(network_address_type_==ipv4) {
    return ipv4_address_.to_string();
  } else if(network_address_type_==ipv6) {
    return ipv6_address_.to_string();
  } else if(network_address_type_==ethernet) {

  }
  return std::string("");
}
