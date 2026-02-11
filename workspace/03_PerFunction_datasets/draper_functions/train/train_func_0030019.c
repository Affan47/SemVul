get_gcs(WinManager *man, int state, int iconified,
		     GC *context1, GC *context2)
{
  GC gc1, gc2;

  switch (man->buttonState[state]) {
  case BUTTON_FLAT:
    gc1 = man->flatContext[state];
    gc2 = man->flatContext[state];
    break;

  case BUTTON_UP:
  case BUTTON_EDGEUP:
    gc1 = man->reliefContext[state];
    gc2 = man->shadowContext[state];
    break;

  case BUTTON_DOWN:
  case BUTTON_EDGEDOWN:
    gc1 = man->shadowContext[state];
    gc2 = man->reliefContext[state];
    break;

  default:
    ConsoleMessage("Internal error in get_gcs\n");
    return;
  }

  if (((man->rev == REVERSE_ICON) && iconified)
      || ((man->rev == REVERSE_NORMAL) && !iconified)) {
    *context1 = gc2;
    *context2 = gc1;
  } else {
    *context1 = gc1;
    *context2 = gc2;
  }
  return;
}
