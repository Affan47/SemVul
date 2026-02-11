dump_output_vsmxdec (char *dest, void *buf, rRCOEntry * entry, void *arg)
{
  VsmxMem *vm = readVSMXMem (buf);
  FILE *fp = openwrite (dest);

  if (fp) {
    if (VsmxDecode (vm, fp)) {
      warning ("Unable to decode VSMX.  Dumping as data instead.");
      freeVsmxMem (vm);
      fclose (fp);
      return dump_output_data (dest, buf, entry, arg);
    }
    freeVsmxMem (vm);
    fclose (fp);
    return TRUE;
  }
  warning ("Unable to open to file '%s'.", dest);
  return FALSE;
}
