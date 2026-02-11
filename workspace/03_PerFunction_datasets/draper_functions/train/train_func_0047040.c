sanei_hp_optset_output_8bit (HpOptSet this, HpData data)
{
  HpOption option_out8;
  int out8;

  option_out8 = hp_optset_get(this, OUT8);
  if (option_out8)
  {
    out8 = hp_option_getint(option_out8, data);
    return out8;
  }
  return 0;
}
