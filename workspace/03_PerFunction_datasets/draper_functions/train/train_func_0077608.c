change_landmark(ElementT *e)
{
  int colon = e->landmark().find_right(':');
  if (colon >= 0)
    e->set_landmark(e->landmark().substring(0, colon) + "<click-fastclassifier>" + e->landmark().substring(colon));
  else
    e->set_landmark(e->landmark() + "<click-fastclassifier>");
}
