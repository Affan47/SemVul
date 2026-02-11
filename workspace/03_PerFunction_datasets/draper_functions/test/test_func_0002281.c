HandleTopLevelDecl(DeclGroupRef D)
{
  for (DeclGroupRef::iterator I = D.begin(), E = D.end(); I != E; ++I) {
    AggregateAccessVisitor->TraverseDecl(*I);
  }
  return true;
}
