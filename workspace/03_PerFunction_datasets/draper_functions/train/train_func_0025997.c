genie_constant (NODE_T * p)
{
  PUSH (p, CONSTANT (GINFO (p)), SIZE (GINFO (p)));
  return (GPROP (p));
}
