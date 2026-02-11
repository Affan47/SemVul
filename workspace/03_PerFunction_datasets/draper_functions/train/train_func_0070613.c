getLeader() {
  Node *N = this;
  Node *Parent = parent.getPointer();
  Node *Grandparent = Parent->parent.getPointer();

  while (Parent != Grandparent) {
    N->parent.setPointer(Grandparent);
    N = Grandparent;
    Parent = Parent->parent.getPointer();
    Grandparent = Parent->parent.getPointer();
  }

  return Parent;
}
