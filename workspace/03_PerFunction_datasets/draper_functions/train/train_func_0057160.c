displayed(Fl_Tree_Item *item) {
  item = item ? item : first();
  if (!item) return(0);
  return( (item->y() >= y()) && (item->y() <= (y()+h()-item->h())) ? 1 : 0);
}
