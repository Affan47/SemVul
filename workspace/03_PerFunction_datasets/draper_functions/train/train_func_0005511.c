ParseAddress(const buzz::XmlElement* elem,
                                   const buzz::QName& address_name,
                                   const buzz::QName& port_name,
                                   talk_base::SocketAddress* address,
                                   ParseError* error) {
  if (!elem->HasAttr(address_name))
    return BadParse("address does not have " + address_name.LocalPart(), error);
  if (!elem->HasAttr(port_name))
    return BadParse("address does not have " + port_name.LocalPart(), error);

  address->SetIP(elem->Attr(address_name));
  std::istringstream ist(elem->Attr(port_name));
  int port = 0;
  ist >> port;
  address->SetPort(port);

  return true;
}
