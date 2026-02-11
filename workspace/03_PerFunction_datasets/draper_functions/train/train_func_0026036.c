add_raw(KCTFile &kct_file, char *filename)
{
  FILE *f;
  int len;
  kct_error_t err;
  byte_t buf[65536];

  if (_verbose > 0)
    cout << "* processing raw file `" << filename << "'...\n";

  f = fopen(filename, "rb");
  if (f == NULL)
    return KCT_ERROR_IO;

  len = fread(buf, 1, 65536, f);
  fclose(f);

  err = kct_file.write(filename, buf, len, 0x0000, 0x0000,
		       KCT_TYPE_BIN, KCT_MACHINE_ALL);

  return err;
}
