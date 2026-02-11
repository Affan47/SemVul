MarkRoots(RootMarkingVisitor* visitor) {


  Heap::IterateStrongRoots(visitor, VISIT_ONLY_STRONG);


  MarkSymbolTable();


  while (marking_stack.overflowed()) {
    RefillMarkingStack();
    EmptyMarkingStack();
  }
}
