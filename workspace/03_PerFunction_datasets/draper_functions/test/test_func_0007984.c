computer_move(int help) {
  if (!playing) return;
  cursor(FL_CURSOR_WAIT);
  Fl::flush();
  busy = 1; abortflag = 0;
  node* move = calcmove(root);
  busy = 0;
  if (move) {
    if (!help && move->value <= -30000) {
      fl_message("%s resigns", move->who ? "White" : "Black");
      playing = autoplay = 0;
      cursor(FL_CURSOR_DEFAULT);
      return;
    }
    animate(move,0);
    domove(move);
  }
  expandnode(root);
  if (!root->son) {
    fl_message("%s has no move", root->who ? "Black" : "White");
    playing = autoplay = 0;
  }
  if (!autoplay) cursor(FL_CURSOR_DEFAULT);
}
