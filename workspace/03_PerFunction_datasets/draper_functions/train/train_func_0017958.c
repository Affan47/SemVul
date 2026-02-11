is_whitelisted(const char *ip) {
  char hashkey[128];
  char octet[4][4];
  char *dip;
  char *oct;
  int i = 0;

  memset(octet, 0, 16);
  dip = strdup(ip);
  if (dip == NULL)
    return 0;

  oct = strtok(dip, ".");
  while(oct != NULL && i<4) {
    if (strlen(oct)<=3)
      strcpy(octet[i], oct);
    i++;
    oct = strtok(NULL, ".");
  }
  free(dip);


  snprintf(hashkey, sizeof(hashkey), "WHITELIST_%s", ip);
  if (ntt_find(hit_list, hashkey)!=NULL)
    return 1;


  snprintf(hashkey, sizeof(hashkey), "WHITELIST_%s.*.*.*", octet[0]);
  if (ntt_find(hit_list, hashkey)!=NULL)
    return 1;

  snprintf(hashkey, sizeof(hashkey), "WHITELIST_%s.%s.*.*", octet[0], octet[1]);
  if (ntt_find(hit_list, hashkey)!=NULL)
    return 1;

  snprintf(hashkey, sizeof(hashkey), "WHITELIST_%s.%s.%s.*", octet[0], octet[1], octet[2]);
  if (ntt_find(hit_list, hashkey)!=NULL)
    return 1;


  return 0;
}
