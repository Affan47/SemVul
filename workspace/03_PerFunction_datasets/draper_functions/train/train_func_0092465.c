write (int reg, int val)
{
  switch (currType)
  {
  case TYPE_OPL2:
  case TYPE_DUAL_OPL2:
    OPLWrite (opl[currChip], 0, reg);
    OPLWrite (opl[currChip], 1, val);
    break;
  case TYPE_OPL3:
    break;
  }
}
