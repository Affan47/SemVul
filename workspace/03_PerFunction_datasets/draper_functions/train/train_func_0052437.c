insertEdgeInternal(Function &Callee) {
  if (Node *N = G->lookup(Callee))
    return insertEdgeInternal(*N);

  CalleeIndexMap.insert(std::make_pair(&Callee, Callees.size()));
  Callees.push_back(&Callee);
}
