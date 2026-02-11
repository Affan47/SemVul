SystemMouseMotion(int x, int y) {
  if(current)
    if(current->mouseMotion != NULL)
      current->mouseMotion(x, y);
}
