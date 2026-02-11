enable_ports (QC_Device * q)
{

  if (q->port < 0x278 || q->port > 0x3bc)
    return SANE_STATUS_INVAL;

  if (ioperm (q->port, 3, 1) < 0)
    return SANE_STATUS_INVAL;

  return SANE_STATUS_GOOD;
}
