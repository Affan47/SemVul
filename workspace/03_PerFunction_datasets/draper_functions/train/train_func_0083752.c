mouse(int b, int s, int x, int y)
{
  float selx, sely;

  mousex = x;
  mousey = y;
  curX = x;
  curY = y;
  if (s == GLUT_DOWN) {
    switch (b) {
    case GLUT_LEFT_BUTTON:
      if (solving) {
        freeSolutions();
        solving = 0;
      glutChangeToMenuEntry(1, (char *)"Solving", 1);
        glutSetWindowTitle((char *)"glpuzzle");
        movingPiece = 0;
      }
      left_mouse = GL_TRUE;
      sel_piece = selectPiece(mousex, mousey);
      if (!sel_piece) {
      left_mouse = GL_FALSE;
      middle_mouse = GL_TRUE;
      } else if (computeCoords(sel_piece, mousex, mousey, &selx, &sely)) {
        grabPiece(sel_piece, selx, sely);
      }
      glutPostRedisplay();
      break;
    case GLUT_MIDDLE_BUTTON:
      middle_mouse = GL_TRUE;
      glutPostRedisplay();
      break;
    }
  } else {
    if (left_mouse) {
      left_mouse = GL_FALSE;
      dropSelection();
      glutPostRedisplay();
    } else if (middle_mouse) {
      middle_mouse = GL_FALSE;
      glutPostRedisplay();
    }
  }
  motion(x, y);
}
