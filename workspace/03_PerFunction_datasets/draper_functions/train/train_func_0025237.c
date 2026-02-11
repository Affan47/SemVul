OGL_set_std_window(OGL_WINDOW *ogl_win)
{
  Bool res = false;

  if (ogl_win) {

    res = glXMakeCurrent(ogl_win->dpy, ogl_win->win, ogl_win->context);

    glViewport(0, 0, ogl_win->width, ogl_win->height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(ogl_win->xmin[0], ogl_win->xmax[0],
	    ogl_win->xmin[1], ogl_win->xmax[1],
	    -1.0, 1.0);
  }
  return res;
}
