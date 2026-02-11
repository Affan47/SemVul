main(int argc, char ** argv) {
  window = new Fl_Double_Window(COLS*W,ROWS*H+60);
bt("@->");
bt("@>");
bt("@>>");
bt("@>|");
bt("@>[]");
bt("@|>");
bt("@<-");
bt("@<");
bt("@<<");
bt("@|<");
bt("@[]<");
bt("@<|");
bt("@<->");
bt("@-->");
bt("@+");
bt("@->|");
bt("@||");
bt("@arrow");
bt("@returnarrow");
bt("@square");
bt("@circle");
bt("@line");
bt("@menu");
bt("@UpArrow");
bt("@DnArrow");
bt("@search");
bt("@FLTK");
bt("@filenew");
bt("@fileopen");
bt("@filesave");
bt("@filesaveas");
bt("@fileprint");
bt("@refresh");
bt("@reload");
bt("@undo");
bt("@redo");

  orientation = new Fl_Value_Slider(
    (int)(window->w()*.05+.5), window->h()-40,
    (int)(window->w()*.42+.5), 16, "Orientation");
  orientation->type(FL_HORIZONTAL);
  orientation->range(0.0, 9.0);
  orientation->value(0.0);
  orientation->step(1);
  orientation->callback(slider_cb, 0);

  size = new Fl_Value_Slider(
    (int)(window->w()*.53+.5), window->h()-40,
    (int)(window->w()*.42+.5), 16, "Size");
  size->type(FL_HORIZONTAL);
  size->range(-3.0, 9.0);
  size->value(0.0);
  size->step(1);
  size->callback(slider_cb, 0);

  window->resizable(window);
  window->show(argc,argv);
  return Fl::run();
}
