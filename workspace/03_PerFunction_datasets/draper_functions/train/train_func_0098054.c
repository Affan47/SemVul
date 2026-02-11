glutGet(GLenum type) {
  switch (type) {
  case GLUT_RETURN_ZERO: return 0;
  case GLUT_WINDOW_X: return glut_window->x();
  case GLUT_WINDOW_Y: return glut_window->y();
  case GLUT_WINDOW_WIDTH: return glut_window->w();
  case GLUT_WINDOW_HEIGHT: return glut_window->h();
  case GLUT_WINDOW_PARENT:
    if (glut_window->parent())
      return ((Fl_Glut_Window *)(glut_window->parent()))->number;
    else
      return 0;


  case GLUT_SCREEN_WIDTH: return Fl::w();
  case GLUT_SCREEN_HEIGHT: return Fl::h();


  case GLUT_MENU_NUM_ITEMS: return menus[glut_menu].size;
  case GLUT_DISPLAY_MODE_POSSIBLE: return Fl_Gl_Window::can_do(glut_mode);
  case GLUT_INIT_WINDOW_X: return initx;
  case GLUT_INIT_WINDOW_Y: return inity;
  case GLUT_INIT_WINDOW_WIDTH: return initw;
  case GLUT_INIT_WINDOW_HEIGHT: return inith;
  case GLUT_INIT_DISPLAY_MODE: return glut_mode;

  case GLUT_WINDOW_BUFFER_SIZE:
    if (glutGet(GLUT_WINDOW_RGBA))
      return glutGet(GLUT_WINDOW_RED_SIZE)+
	glutGet(GLUT_WINDOW_GREEN_SIZE)+
	glutGet(GLUT_WINDOW_BLUE_SIZE)+
	glutGet(GLUT_WINDOW_ALPHA_SIZE);
    else
      return glutGet(GLUT_WINDOW_COLORMAP_SIZE);
  case GLUT_VERSION: return 20400;
  default: {GLint p; glGetIntegerv(type, &p); return p;}
  }
}
