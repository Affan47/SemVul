opShowSpaceText(Object args[], int numArgs) {
  Array *a;
  Object obj;
  int wMode;
  int i;

  if (!state->getFont()) {
#ifdef POPPLER_NEW_ERRORAPI
    error(errSyntaxError, getPos(), "No font in show/space");
#else
    error(getPos(), const_cast<char*>("No font in show/space"));
#endif
    return;
  }
  if (fontChanged) {
    builder->updateFont(state);
    fontChanged = gFalse;
  }
  wMode = state->getFont()->getWMode();
  a = args[0].getArray();
  for (i = 0; i < a->getLength(); ++i) {
    a->get(i, &obj);
    if (obj.isNum()) {


      if (wMode) {
	state->textShift(0, -obj.getNum() * 0.001 *
			    fabs(state->getFontSize()));
      } else {
	state->textShift(-obj.getNum() * 0.001 *
			 fabs(state->getFontSize()), 0);
      }
      builder->updateTextShift(state, obj.getNum());
    } else if (obj.isString()) {
      doShowText(obj.getString());
    } else {
#ifdef POPPLER_NEW_ERRORAPI
      error(errSyntaxError, getPos(), "Element of show/space array must be number or string");
#else
      error(getPos(), const_cast<char*>("Element of show/space array must be number or string"));
#endif
    }
    obj.free();
  }
}
