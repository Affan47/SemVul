print_ports(OMSTREAM& o, const COMPONENT* x)
{
  assert(x);

  o << " (";
  std::string sep = "";
  for (int ii = 0;  x->port_exists(ii);  ++ii) {
    o << sep << x->port_value(ii);
    sep = " ";
  }
  for (int ii = 0;  x->current_port_exists(ii);  ++ii) {
    o << sep << x->current_port_value(ii);
    sep = " ";
  }
  o << ")";
}
