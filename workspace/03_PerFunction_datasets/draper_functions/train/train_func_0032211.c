VHDL_signal ()
{
  char  sBusWide[SIZE_SNAME];


  VHDL_BUS_WIDE (sBusWide, LV_N - 1, 0);

  switch (LV_Function) {
    case DPGEN_MUX2:
    case DPGEN_BUSE:
    case DPGEN_NBUSE:
      break;
    case DPGEN_NAND2MASK:
    case DPGEN_NOR2MASK:
    case DPGEN_XNOR2MASK:
    case DPGEN_NMUX2:
      fprintf (LV_FILE, "  SIGNAL %20s : BIT_VECTOR %s;\n", "q", sBusWide);
      break;
    case DPGEN_DFFT:
    case DPGEN_SFFT:
      fprintf (LV_FILE, "  SIGNAL %20s : BIT_VECTOR %s;\n",
               "d_test", sBusWide);
    case DPGEN_DFF:
    case DPGEN_SFF:
      fprintf (LV_FILE, "  SIGNAL %20s : BIT_VECTOR %s;\n",
               "d_wen", sBusWide);
      fprintf (LV_FILE, "  SIGNAL %20s : REG_VECTOR %s REGISTER;\n",
               "ff", sBusWide);
      break;
  }

  fprintf (LV_FILE, "\n");
}
