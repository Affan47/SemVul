cb_showselected_button(Fl_Button*, void*) {
  fprintf(stderr, "--- SELECTED ITEMS\n");
for ( Fl_Tree_Item *item = tree->first_selected_item();
      item;
      item = tree->next_selected_item(item) ) {
  fprintf(stderr, "\t%s\n", item->label() ? item->label() : "???");
};
}
