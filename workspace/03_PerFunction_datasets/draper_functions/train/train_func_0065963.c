markModified(STNode * pos) {
  while (pos != NULL) {
    if (pos->modified == 1)
      break;
    pos->modified = 1;
    pos = pos->parent;
  }
}
