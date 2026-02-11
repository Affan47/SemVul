shortest() const {
  register FXfloat x=upper.x-lower.x;
  register FXfloat y=upper.y-lower.y;
  return FXMIN(x,y);
  }
