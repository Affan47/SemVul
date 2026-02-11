parse_instance(CS& cmd, COMPONENT* x)
{
  cmd.reset();
  parse_label(cmd, x);
  parse_ports(cmd, x);
  parse_type(cmd, x);
  parse_args(cmd, x);
  cmd.check(bWARNING, "what's this?");
  return x;
}
