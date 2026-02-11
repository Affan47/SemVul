drawImageMask(GfxState *state, Object *ref, Stream *str,
				   int width, int height, GBool invert,
				   GBool interpolate, GBool inlineImg) {
  FILE *f;
  int c;
  int size, i;


  if (dumpJPEG && str->getKind() == strDCT && !inlineImg) {


    setFilename("jpg");
    ++imgNum;
    if (!(f = fopen(fileName, "wb"))) {
      error(-1, "Couldn't open image file '%s'", fileName);
      return;
    }


    str = str->getNextStream();
    str->reset();


    while ((c = str->getChar()) != EOF)
      fputc(c, f);

    str->close();
    fclose(f);


  } else {


    setFilename("pbm");
    ++imgNum;
    if (!(f = fopen(fileName, "wb"))) {
      error(-1, "Couldn't open image file '%s'", fileName);
      return;
    }
    fprintf(f, "P4\n");
    fprintf(f, "%d %d\n", width, height);


    str->reset();


    size = height * ((width + 7) / 8);
    for (i = 0; i < size; ++i) {
      fputc(str->getChar(), f);
    }

    str->close();
    fclose(f);
  }
}
