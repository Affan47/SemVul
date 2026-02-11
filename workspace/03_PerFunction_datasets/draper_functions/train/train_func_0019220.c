construct(const char *name)
{

  P12F683 *p = new P12F683(name);

  p->create(0x7f, 256);
  p->create_invalid_registers ();
  p->create_symbols();
  return p;

}
