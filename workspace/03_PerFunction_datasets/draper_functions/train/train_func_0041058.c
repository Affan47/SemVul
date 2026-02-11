parsearg(const char *var, const char *value)
{
    if (strcmp(var, "display") == 0) {
	  strncpy (mycmd, value, sizeof(mycmd));
          mycmd[sizeof(mycmd) - 1] = '\0';

    } else if (strcmp(var, "value") == 0) {
	  strncpy (upsval, value, sizeof(upsval));
          upsval[sizeof(upsval) - 1] = '\0';

    } else if (strcmp(var, "value2") == 0) {
	  strncpy (upsval2, value, sizeof(upsval2));
          upsval2[sizeof(upsval2) - 1] = '\0';

    } else if (strcmp(var, "value3") == 0) {
	  strncpy (upsval3, value, sizeof(upsval3));
          upsval3[sizeof(upsval3) - 1] = '\0';
    }
}
