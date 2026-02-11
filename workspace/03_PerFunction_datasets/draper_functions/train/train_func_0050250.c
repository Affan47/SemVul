lookup(CODE code, OVECTOR name, uint16_t *frame, uint16_t *offset) {
  VECTOR currcell;
  uint16_t frameno;

  currcell = code->scope;
  frameno = 0;

  while (currcell != NULL) {
    VECTOR currframe = (VECTOR) CAR(currcell);
    uint16_t i;

    for (i = 0; i < currframe->_.length; i++)
      if (AT(currframe, i) == (OBJ) name) {
	if (frame != NULL)
	  *frame = frameno;
	if (offset != NULL)
	  *offset = i;
	return 1;
      }

    frameno++;
    currcell = (VECTOR) CDR(currcell);
  }

  return 0;
}
