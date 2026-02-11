gdk_gl_context_share_new(GdkVisual *visual, GdkGLContext *sharelist, gint direct)
{
#if defined GDK_WINDOWING_WIN32
  GdkGLContext *context;
#elif defined GDK_WINDOWING_X11
  Display *dpy;
  XVisualInfo *vi;
  GLXContext glxcontext;
  GdkGLContext *context;
#else
  g_warning ("gdk_gl_context_share_new not implemented on " PLATFORM);
  return NULL;
#endif

  g_return_val_if_fail (visual != NULL, NULL);

  context = g_object_new(GDK_TYPE_GL_CONTEXT, NULL);
  if (!context)
    return NULL;

#if defined GDK_WINDOWING_WIN32
  context->initialised = FALSE;
  context->hglrc   = NULL;
  context->hdc     = NULL;
  context->hwnd    = NULL;
  context->share   = sharelist ? g_object_ref(sharelist) : NULL;

  memset (&(context->pfd), 0, sizeof(PIXELFORMATDESCRIPTOR));


  context->pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  context->pfd.nVersion = 1;
  if (direct)
    context->pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
  else
    context->pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_BITMAP | PFD_SUPPORT_GDI;
  context->pfd.iPixelType = PFD_TYPE_RGBA;
  context->pfd.cColorBits = 24;
  context->pfd.cDepthBits = 32;
  context->pfd.iLayerType = PFD_MAIN_PLANE;
#elif defined GDK_WINDOWING_X11
  dpy = GDK_DISPLAY();

  vi = get_xvisualinfo(visual);

  glxcontext = glXCreateContext(dpy, vi, sharelist ? sharelist->glxcontext : 0,
                                direct ? True : False);

  XFree(vi);
  if (glxcontext == NULL) {
    g_object_unref(context);
    return NULL;
  }

  context->xdisplay = dpy;
  context->glxcontext = glxcontext;
#endif

  return context;
}
