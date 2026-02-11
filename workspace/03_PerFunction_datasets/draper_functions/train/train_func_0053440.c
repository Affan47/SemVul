cb_testrootshowself_button(Fl_Button*, void*) {
  Fl_Tree_Item *root = tree->root();
fprintf(stderr, "--- Show Tree\n");
if (root) root->show_self();
}
