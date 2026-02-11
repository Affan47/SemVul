inCorner(FXint x,FXint y) const {
  register FXint rx=x-dialx-ringouter;
  register FXint ry=y-dialy-ringouter;
  return (ringouter*ringouter<=rx*rx+ry*ry) && (0.99999f<=hsv[1] && 0.99999f<=hsv[2]);
  }
