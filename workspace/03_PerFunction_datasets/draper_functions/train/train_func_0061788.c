config_mac_address_string2int (pstdout_state_t pstate,
                               const char *src,
                               uint64_t *dest)
{
  unsigned int b1, b2, b3, b4, b5, b6;
  uint64_t val;
  int ret;

  assert (src && dest);

  if ((ret = sscanf (src,
                     "%02X:%02X:%02X:%02X:%02X:%02X",
                     &b1,
                     &b2,
                     &b3,
                     &b4,
                     &b5,
                     &b6)) < 0)
    {
      PSTDOUT_PERROR (pstate, "sscanf");
      return (-1);
    }

  if (ret != 6)
    {
      PSTDOUT_FPRINTF (pstate,
                       stderr,
                       "config_mac_address_string2int: Invalid src input: %s\n",
                       src);
      return (-1);
    }

  val = 0;
  val |= (uint64_t)b1;
  val |= ((uint64_t)b2 << 8);
  val |= ((uint64_t)b3 << 16);
  val |= ((uint64_t)b4 << 24);
  val |= ((uint64_t)b5 << 32);
  val |= ((uint64_t)b6 << 40);

  *dest = val;
  return (0);
}
