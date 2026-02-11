glutIdleFunc(void (*f)())
{

  if(glut_idle_func == f) return;

  if(glut_idle_func) Fl::remove_idle((void (*)(void *))glut_idle_func);

  if(f) Fl::add_idle((void (*)(void *))f);

  glut_idle_func = f;
}
