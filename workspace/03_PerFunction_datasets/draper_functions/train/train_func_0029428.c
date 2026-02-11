main(int argc, char **argv)
{
  long i;

  glutInit(&argc, argv);
  for (i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      switch (argv[i][1]) {
      case 's':
        doubleBuffer = 0;
        break;
      default:
        Usage();
      }
    } else {
      Usage();
    }
  }

  glutInitWindowSize(W, H);
  if (doubleBuffer) {
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE | GLUT_MULTISAMPLE);
  } else {
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_SINGLE | GLUT_MULTISAMPLE);
  }

  glutCreateWindow("glpuzzle");
  visible = 1;

  init();

  glGetIntegerv(GL_VIEWPORT, viewport);

  puts("");
  puts("r   Reset puzzle");
  puts("s   Solve puzzle (may take a few seconds to compute)");
  puts("d   Destroy a piece - makes the puzzle easier");
  puts("b   Toggles the depth buffer on and off");
  puts("");
  puts("Left mouse moves pieces");
  puts("Middle mouse spins the puzzle");
  puts("Right mouse has menu");

  glutReshapeFunc(Reshape);
  glutDisplayFunc(redraw);
  glutKeyboardFunc(keyboard);
  glutMotionFunc(motion);
  glutMouseFunc(mouse);
  glutVisibilityFunc(visibility);
  glutCreateMenu(menu);
  glutAddMenuEntry((char *)"Solve", 1);
  glutAddMenuEntry((char *)"Reset", 2);
  glutAddMenuEntry((char *)"Quit", 3);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutMainLoop();
  return 0;
}
