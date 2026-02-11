cb_exit(Fl_Button*, void*) {
  if(fnt_chooser_win) fnt_chooser_win->hide();
  if(main_win) main_win->hide();
}
