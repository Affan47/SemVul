gtab_key2name(INMD *tinmd, u_int64_t key, char *t, int *rtlen)
{
    int tlen=0, klen=0;

    int j;
    for(j=Max_tab_key_num1(tinmd) - 1; j>=0; j--) {
      int sh = j * KeyBits1(tinmd);
      int k = (key >> sh) & tinmd->kmask;

      if (!k)
        break;
      int len;
      char *keyname;

      if (tinmd->keyname_lookup) {
        len = 1;
        keyname = (char *)&tinmd->keyname_lookup[k];
      } else {
        keyname = (char *)&tinmd->keyname[k * CH_SZ];
        len = (*keyname & 0x80) ? utf8_sz(keyname) : strlen(keyname);
      }

      memcpy(&t[tlen], keyname, len);
      tlen+=len;
      klen++;
    }

    t[tlen]=0;
    *rtlen = tlen;
    return klen;
}
