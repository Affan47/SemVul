addMod(LDAPMod ***modary, int *capacity, int *nmods, LDAPMod *toadd)
{
  if (*nmods == *capacity) {
    *capacity += 4;
    if (*modary) {
      *modary = (LDAPMod **)slapi_ch_realloc((char *)*modary, *capacity * sizeof(LDAPMod *));
    } else {
      *modary = (LDAPMod **)slapi_ch_malloc(*capacity * sizeof(LDAPMod *));
    }
  }
  (*modary)[*nmods] = toadd;
  (*nmods)++;
}
