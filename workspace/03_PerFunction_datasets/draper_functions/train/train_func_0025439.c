last() {
  if ( ! _root ) return(0);
  Fl_Tree_Item *item = _root;
  while ( item->has_children() ) {
    item = item->child(item->children()-1);
  }
  return(item);
}
