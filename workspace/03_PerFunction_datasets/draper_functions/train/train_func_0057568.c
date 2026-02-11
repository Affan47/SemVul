constexprToEdges(CFLAAResult &Analysis,
                             ConstantExpr &CExprToCollapse,
                             SmallVectorImpl<Edge> &Results) {
  SmallVector<ConstantExpr *, 4> Worklist;
  Worklist.push_back(&CExprToCollapse);

  SmallVector<Edge, 8> ConstexprEdges;
  SmallPtrSet<ConstantExpr *, 4> Visited;
  while (!Worklist.empty()) {
    auto *CExpr = Worklist.pop_back_val();

    if (!hasUsefulEdges(CExpr))
      continue;

    ConstexprEdges.clear();
    argsToEdges(Analysis, CExpr, ConstexprEdges);
    for (auto &Edge : ConstexprEdges) {
      if (auto *Nested = dyn_cast<ConstantExpr>(Edge.From))
        if (Visited.insert(Nested).second)
          Worklist.push_back(Nested);

      if (auto *Nested = dyn_cast<ConstantExpr>(Edge.To))
        if (Visited.insert(Nested).second)
          Worklist.push_back(Nested);
    }

    Results.append(ConstexprEdges.begin(), ConstexprEdges.end());
  }
}
