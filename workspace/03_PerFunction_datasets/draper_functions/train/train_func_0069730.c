rcoxml_add_label (char **labels, uint32_t * labelsLen, char *label,
    uint8_t eventQuirk)
{

  uint32_t p = 0;

  while (p < *labelsLen && (*labels)[p]) {
    if (!strcmp (*labels + p, label))
      return p;
    p += strlen (*labels + p) + 1;
    p = ALIGN_TO_4 (p);


  }


  uint32_t curLen = *labelsLen;
  uint32_t labelLen = strlen (label) + 1;

  if (eventQuirk) {

  }
  uint32_t newLen = curLen + labelLen;

  newLen = ALIGN_TO_4 (newLen);

  *labels = (char *) realloc (*labels, newLen);
  strcpy (*labels + curLen, label);
  if (labelLen % 4) {
    memset (*labels + curLen + labelLen, 0, 4 - (labelLen % 4));
  }
  *labelsLen = newLen;


  return curLen;
}
