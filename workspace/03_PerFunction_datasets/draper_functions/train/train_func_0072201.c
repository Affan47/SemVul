_iodbcdm_cfg_rewind (PCONFIG pconfig)
{
  if (!_iodbcdm_cfg_valid (pconfig))
    return -1;

  pconfig->flags = CFG_VALID;
  pconfig->cursor = 0;

  return 0;
}
