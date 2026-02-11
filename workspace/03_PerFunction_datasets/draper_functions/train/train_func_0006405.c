pin2juyin(gboolean full_match)
{
  int i;

  char pin[8];
  bzero(poo.typ_pho, sizeof(poo.typ_pho));
  if (poo.inph[0]=='`') {
    poo.typ_pho[0]=BACK_QUOTE_NO;
    poo.typ_pho[1]=poo.inph[1];
    return TRUE;
  }

  int inphN = strlen(poo.inph);
  for(i=0; i < pin_juyinN; i++) {
    bzero(pin, sizeof(pin));
    memcpy(pin,  pin_juyin[i].pinyin, sizeof(pin_juyin[0].pinyin));

    int pinN = strlen(pin);
    if (pinN < inphN)
      continue;

    if (full_match && pinN != inphN)
      continue;

    if (!memcmp(pin, poo.inph, inphN)) {


      break;
    }
  }

  if (i==pin_juyinN) {
    dbg("pin2juyin not found ..\n");
    return FALSE;
  }

  bzero(poo.typ_pho, sizeof(poo.typ_pho));

  key_typ_pho(pin_juyin[i].key, (u_char *)poo.typ_pho);


  return TRUE;
}
