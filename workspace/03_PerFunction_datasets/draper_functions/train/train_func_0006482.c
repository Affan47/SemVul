parse_comment(CS& cmd, DEV_COMMENT* x)
{
  assert(x);
  x->set(cmd.fullstring());
  return x;
}
