glutCreateMenu(void (*cb)(int)) {
  int i;
  for (i=1; i<MAXMENUS; i++) if (!menus[i].cb) break;
  menu *m = &menus[i];
  m->cb = cb;
  return glut_menu = i;
}
