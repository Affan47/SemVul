motion(int x, int y)
{
  float selx, sely;

  if (middle_mouse && !left_mouse) {
    if (mousex != x || mousey != y) {
      trackball(lastquat,
        (2.0*mousex - W) / W,
        (H - 2.0*mousey) / H,
        (2.0*x - W) / W,
        (H - 2.0*y) / H);
      spinning = 1;
    } else {
      spinning = 0;
    }
    changeState();
  } else {
    computeCoords(sel_piece, x, y, &selx, &sely);
    moveSelection(selx, sely);
  }
  mousex = x;
  mousey = y;
  glutPostRedisplay();
}
