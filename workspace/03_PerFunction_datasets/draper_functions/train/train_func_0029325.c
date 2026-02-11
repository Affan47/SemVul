_probe_gamma_vector (_HpOption this, HpScsi scsi, HpOptSet optset, HpData data)
{
  SANE_Fixed *	buf;
  int		i;
  size_t	size, length;

  RETURN_IF_FAIL( _probe_vector(this, scsi, optset, data) );


  size = hp_option_saneoption(this, data)->size;
  if (!(buf = alloca(size)))
      return SANE_STATUS_NO_MEM;
  length = size / sizeof(SANE_Fixed);
  for (i = 0; i < (int)length; i++)
      buf[i] = (SANE_FIX(HP_VECTOR_SCALE* 1.0) * i + (length-1) / 2) / length;
  return sanei_hp_accessor_set(this->data_acsr, data, buf);
}
