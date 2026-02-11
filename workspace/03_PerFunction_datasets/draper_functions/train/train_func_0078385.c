extend_selection(Fl_Tree_Item *from, Fl_Tree_Item *to) {
  char on = 0;
  if ( from == to ) {
    from->select();
    return;
  }
  for ( Fl_Tree_Item *item = first(); item; item = next(item) ) {
    if ( (item == from) || (item == to) ) {
      item->select();
      on ^= 1;
    } else if ( on ) {
      item->select();
    }
  }
}
