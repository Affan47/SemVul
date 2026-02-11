diagrams(const DiagramVector & diags) const {
  Selector<DiagramIndex> sel;
  for ( DiagramIndex i = 0; i < diags.size(); ++i )
    sel.insert(meInfo()[abs(diags[i]->id())-1], i);
  return sel;
}
