c_common_print_pch_checksum (FILE *f)
{
  int i;
  fputs ("Compiler executable checksum: ", f);
  for (i = 0; i < 16; i++)
    fprintf (f, "%02x", executable_checksum[i]);
  putc ('\n', f);
}
