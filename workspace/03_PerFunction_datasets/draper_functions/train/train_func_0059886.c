compare_appname(Application *a, Application *b)
{
  return string(a->name())<string(b->name());
}
