opCloseStroke(Object * , int ) {
  if (!state->isCurPt()) {

    return;
  }
  state->closePath();
  if (state->isPath() && !contentIsHidden()) {
    if (state->getStrokeColorSpace()->getMode() == csPattern) {
      doPatternStroke();
    } else {
      out->stroke(state);
    }
  }
  doEndPath();
}
