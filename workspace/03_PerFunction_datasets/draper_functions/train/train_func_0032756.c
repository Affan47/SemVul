open(const char *filename)
{
  if (Z80::open(filename) != 0) { return -1; }

  if (model == TI84_PLUS)
  {
    fprintf(out, ".include \"ti84plus.inc\"\n\n");
  }
    else
  {
    fprintf(out, ".include \"ti84pcse.inc\"\n\n");
  }
  fprintf(out, "save_iy equ appData\n");
  fprintf(out, "save_ix equ appData+2\n");
  fprintf(out, "ram_start equ appData+4\n");
  fprintf(out, "heap_ptr equ ram_start\n");

  return 0;
}
