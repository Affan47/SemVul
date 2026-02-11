gl_visual(int mode, int *alist) {
  Fl_Gl_Choice *c = Fl_Gl_Choice::find(mode,alist);
  if (!c) return 0;
#ifdef WIN32
  gl_choice = c;
#elif defined(__APPLE_QD__)
  gl_choice = c;
#elif defined(__APPLE_QUARTZ__)

  gl_choice = c;
#else
  fl_visual = c->vis;
  fl_colormap = c->colormap;
#endif
  return 1;
}
