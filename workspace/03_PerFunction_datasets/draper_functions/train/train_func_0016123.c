isVisible(GBool printing) {

  if ((flags & flagHidden) ||
      (printing && !(flags & flagPrint)) ||
      (!printing && (flags & flagNoView))) {
    return gFalse;
  }


  if (optContentConfig && oc.isRef()) {
    if (! optContentConfig->optContentIsVisible(&oc))
      return gFalse;
  }

  return gTrue;
}
