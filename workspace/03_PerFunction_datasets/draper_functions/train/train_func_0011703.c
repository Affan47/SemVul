isHorizontalScrollable() const {
  return !((options&HSCROLLER_NEVER) && (options&HSCROLLER_ALWAYS));
  }
