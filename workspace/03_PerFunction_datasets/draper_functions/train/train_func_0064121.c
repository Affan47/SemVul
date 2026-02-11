opSetStrokeColorN(Object args[], int numArgs) {
  GfxColor color;
  GfxPattern *pattern;
  int i;

  if (state->getStrokeColorSpace()->getMode() == csPattern) {
    if (numArgs > 1) {
      if (!((GfxPatternColorSpace *)state->getStrokeColorSpace())
	       ->getUnder() ||
	  numArgs - 1 != ((GfxPatternColorSpace *)state->getStrokeColorSpace())
	                     ->getUnder()->getNComps()) {
#ifdef POPPLER_NEW_ERRORAPI
	error(errSyntaxError, getPos(), "Incorrect number of arguments in 'SCN' command");
#else
	error(getPos(), const_cast<char*>("Incorrect number of arguments in 'SCN' command"));
#endif
	return;
      }
      for (i = 0; i < numArgs - 1 && i < gfxColorMaxComps; ++i) {
	if (args[i].isNum()) {
	  color.c[i] = dblToCol(args[i].getNum());
	}
      }
      state->setStrokeColor(&color);
      builder->updateStyle(state);
    }
#if defined(POPPLER_NEW_COLOR_SPACE_API) || defined(POPPLER_NEW_ERRORAPI)
    if (args[numArgs-1].isName() &&
	(pattern = res->lookupPattern(args[numArgs-1].getName(), NULL))) {
      state->setStrokePattern(pattern);
      builder->updateStyle(state);
    }
#else
    if (args[numArgs-1].isName() &&
	(pattern = res->lookupPattern(args[numArgs-1].getName()))) {
      state->setStrokePattern(pattern);
      builder->updateStyle(state);
    }
#endif

  } else {
    if (numArgs != state->getStrokeColorSpace()->getNComps()) {
#ifdef POPPLER_NEW_ERRORAPI
      error(errSyntaxError, getPos(), "Incorrect number of arguments in 'SCN' command");
#else
      error(getPos(), const_cast<char*>("Incorrect number of arguments in 'SCN' command"));
#endif
      return;
    }
    state->setStrokePattern(NULL);
    for (i = 0; i < numArgs && i < gfxColorMaxComps; ++i) {
      if (args[i].isNum()) {
	color.c[i] = dblToCol(args[i].getNum());
      }
    }
    state->setStrokeColor(&color);
    builder->updateStyle(state);
  }
}
