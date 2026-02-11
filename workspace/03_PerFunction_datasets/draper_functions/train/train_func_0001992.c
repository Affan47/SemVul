indexNodes() {
  for (auto &I : Nodes)
    Lookup[I.Node.Index] = &I;
}
