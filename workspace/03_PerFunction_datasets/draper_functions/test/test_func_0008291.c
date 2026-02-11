makePositionVisible(FXint pos) {
  FXint xPos, yPos;

  xPos=pos_x;
  yPos=getContentHeight()-viewport_h;
  if (xPos>=0 && yPos>=0)
    setPosition(-xPos, -yPos);
}
