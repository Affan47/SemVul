reset()
{
  int imax = get_size();
  for (int i=0; i<imax; i++) {
    get(i)->reset();
  }
}
