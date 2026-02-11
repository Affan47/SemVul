diagrams(const DiagramVector & diags) const {
  Selector<DiagramIndex> sel;
  if(diags.size()==1) {
    sel.insert(1.0, 0);
  }
  else {
    for ( DiagramIndex i = 0; i < diags.size(); ++i ) {
      if(_swap&&diags[i]->id()==-2)
	sel.insert(1.0, i);
      else if(!_swap&&diags[i]->id()==-1)
	sel.insert(1.0, i);
    }
  }
  return sel;
}
