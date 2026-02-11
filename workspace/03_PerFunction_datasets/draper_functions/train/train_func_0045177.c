zset_attr(void)
{
  check_zero(0, 0);
  check_attr(zargs[1]);

  uint16_t addr = OBJECT(zargs[0]) + (zargs[1] / 8);

  STORE_BYTE(addr, BYTE(addr) | ATTR_BIT(zargs[1]));
}
