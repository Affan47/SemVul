readQpt(gchar *str, float qpt[4], float *disp, guint natom)
{
  gchar **values;
  gchar *ptr;
  guint j, k;

  ptr = strstr(str, "qpt");
  if (!ptr)
    return FALSE;
  ptr = strstr(ptr, "=");
  if (!ptr)
    {
      g_warning("syntax error for meta data 'qpt' in '%s'.", str);
      return FALSE;
    }

  DBG_fprintf(stderr, "Atomic ASCII: read qpt from '%s'\n", ptr);
  memset(disp, 0, sizeof(float) * 6 * natom);
  values = g_strsplit_set(ptr + 1, " [];\n\r\\\t", -1);
  k = 0;
  for (j = 0; values[j] && k < 4; j++)
    if (values[j][0] != '\0')
      {
	if (sscanf(values[j], "%f", qpt + k) != 1)
	  {
	    g_warning("Can't read a float value from qpt"
		      " keyword in '%s'.", values[j]);
	    qpt[k] = 0.f;
	  }
	DBG_fprintf(stderr, " | qpt[%d] = %g\n", k, qpt[k]);
	k += 1;
      }
  if (k != 4)
    g_warning("Can't read 4 float values from qpt"
	      " keyword in '%s'.", ptr);
  for (k = 0; values[j] && k < 6 * natom; j++)
    if (values[j][0] != '\0')
      {
	if (sscanf(values[j], "%f", disp + k) == 1)
	  k += 1;
	if (DEBUG && k % 6 == 5)
	  DBG_fprintf(stderr, " | u[%d] = (%g,%g,%g) + i(%g,%g,%g)\n", k / 6,
		      disp[(k / 6) * 6 + 0], disp[(k / 6) * 6 + 1], disp[(k / 6) * 6 + 2],
		      disp[(k / 6) * 6 + 3], disp[(k / 6) * 6 + 4], disp[(k / 6) * 6 + 5]);
      }
  if (k != natom * 6)
    g_warning("Can't read enough displacement values,"
	      " %d read while %d were awaited.", k, natom * 6);
  g_strfreev(values);

  return TRUE;
}
