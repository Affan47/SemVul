parse_type(CS& cmd, CARD* x)
{
  assert(x);
  std::string new_type;
  cmd >> new_type;
  x->set_dev_type(new_type);
}
