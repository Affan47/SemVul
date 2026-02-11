id3_write_file(char *src, unsigned long size, FILE *fp, char *fn)
{
  if (fwrite(src, size, 1, fp) != 1)
  {
    print_error("id3_write_file: Error writing to %s", fn);
    fclose(fp);
    return FALSE;
  }

  if (ferror(fp) != 0)
  {
    print_error("id3_write_file: Error writing to %s", fn);
    clearerr(fp);
    fclose(fp);
    return FALSE;
  }

  return TRUE;
}
