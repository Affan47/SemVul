RSA_Behav ()
{
  char  sBusWide0[SIZE_SNAME];
  char  sBusWide1[SIZE_SNAME];
  char  sBusWide2[SIZE_SNAME];
  long  i;


  LV_FILE = mbkfopen (LV_modelName, "vbe", WRITE_TEXT);

  if (!LV_FILE) {
    eprinth ("*** dpgen ***");
    eprintf ("\n  Unable to create file \"%s.vbe\".\n", LV_modelName);
    EXIT (1);
  }


  VHDL_BUS_WIDE (sBusWide0, LV_N - 1, 0);
  VHDL_BUS_WIDE (sBusWide1, LV_N    , 1);
  VHDL_BUS_WIDE (sBusWide2, LV_N    , 0);


  fprintf (LV_FILE, "\nENTITY %s IS\n  PORT (\n", LV_modelName);

  fprintf (LV_FILE, "%14s : in    BIT;\n", "add_sub");
  fprintf (LV_FILE, "%14s :   out BIT;\n", "c31");
  fprintf (LV_FILE, "%14s :   out BIT;\n", "c30");
  fprintf (LV_FILE, "%14s : in    BIT_VECTOR %s;\n", "i0", sBusWide0);
  fprintf (LV_FILE, "%14s : in    BIT_VECTOR %s;\n", "i1", sBusWide0);
  fprintf (LV_FILE, "%14s :   out BIT_VECTOR %s;\n",  "q", sBusWide0);
  fprintf (LV_FILE, "%14s : in    BIT;\n", "vdd");
  fprintf (LV_FILE, "%14s : in    BIT\n" , "vss");

  fprintf (LV_FILE, "  );\nEND %s;\n\n\n", LV_modelName);


  fprintf (LV_FILE, "ARCHITECTURE VBE OF %s IS\n\n", LV_modelName);

  fprintf (LV_FILE, "  SIGNAL %20s : BIT_VECTOR %s;\n", "carry", sBusWide2);
  fprintf (LV_FILE, "  SIGNAL %20s : BIT_VECTOR %s;\n", "xor_b", sBusWide0);

  fprintf (LV_FILE, "\nBEGIN\n\n");


  for (i = LV_N - 1; i >= 0; i--)
    fprintf (LV_FILE, "  xor_b(%ld) <= i1(%ld) xor add_sub;\n", i, i);
  fprintf (LV_FILE, "\n");

  fprintf (LV_FILE, "  carry(0) <= add_sub;\n\n");


  fprintf (LV_FILE, "  q <=     i0\n");
  fprintf (LV_FILE, "       xor xor_b\n");
  fprintf (LV_FILE, "       xor carry%s;\n\n", sBusWide0);

  fprintf (LV_FILE, "  c31 <=  carry(%ld);\n"  , LV_N);
  fprintf (LV_FILE, "  c30 <=  carry(%ld);\n\n", LV_N - 1);

  fprintf (LV_FILE, "  carry%s <=      (   i0 and xor_b)\n"       , sBusWide1);
  fprintf (LV_FILE, "               or (   i0 and carry%s)\n"     , sBusWide0);
  fprintf (LV_FILE, "               or (xor_b and carry%s);\n\n\n", sBusWide0);


  fprintf(LV_FILE, "  ASSERT (vdd = '1')\n");
  fprintf(LV_FILE,
          "    REPORT \"Power supply is missing on vdd of model %s.\"\n",
          LV_modelName);
  fprintf(LV_FILE, "    SEVERITY WARNING;\n\n");


  fprintf(LV_FILE, "  ASSERT (vss = '0')\n");
  fprintf(LV_FILE,
          "    REPORT \"Power supply is missing on vss of model %s.\"\n",
          LV_modelName);
  fprintf(LV_FILE, "    SEVERITY WARNING;\n\n");


  fprintf (LV_FILE, "END VBE;\n");


  fclose (LV_FILE);
}
