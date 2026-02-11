next_displayed(Fl_Tree_Prefs &prefs) {
  Fl_Tree_Item *item = this;
  while ( 1 ) {
    item = item->next();
    if ( !item ) return 0;
    if ( item->is_root() && !prefs.showroot() ) continue;
    if ( item->visible_r() ) return(item);
  }
}
