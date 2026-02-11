addChildren(GooList *childrenA) {
  if (!children) {
    children = new GooList();
  }
  children->append(childrenA);
  delete childrenA;
}
