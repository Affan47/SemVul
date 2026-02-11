procfs_check_ac_state(void)
{
  FILE *fp;
  char buf[128];
  int ret;

  fp = fopen(PROC_ACPI_AC_STATE, "r");
  if (fp == NULL)
    return AC_STATE_ERROR;

  ret = fread(buf, 1, 127, fp);

  if (ferror(fp) != 0)
    {
      logdebug("acpi: Error reading proc AC state: %s\n", strerror(errno));
      return AC_STATE_ERROR;
    }

  if (feof(fp) == 0)
    {
      logdebug("acpi: Error reading proc AC state: buffer too small\n");
      return AC_STATE_ERROR;
    }

  fclose(fp);

  buf[ret] = '\0';

  if (strstr(buf, PROC_ACPI_AC_ONLINE) != NULL)
    return AC_STATE_ONLINE;

  if (strstr(buf, PROC_ACPI_AC_OFFLINE) != NULL)
    return AC_STATE_OFFLINE;

  return AC_STATE_UNKNOWN;
}
