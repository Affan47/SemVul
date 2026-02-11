convertStringToBXKey(const char* string)
{

  for (Bit16u i=0; i<BX_KEY_NBKEYS; i++) {
    if (strcmp(string,bx_key_symbol[i])==0) {
      return i;
    }
  }


  return BX_KEYMAP_UNKNOWN;
}
