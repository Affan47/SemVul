getArrowDir() const {
  return (state&ARROW_UP) ? TRUE : (state&ARROW_DOWN) ? FALSE : MAYBE;
  }
