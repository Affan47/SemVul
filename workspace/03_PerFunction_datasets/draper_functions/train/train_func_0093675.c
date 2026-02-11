FLTKmain(int argc, char** argv) {
  Fl::visual(FL_DOUBLE|FL_INDEX);
  Board b(BOARDSIZE,BOARDSIZE);
  b.color(FL_BACKGROUND_COLOR);
  b.callback(quit_cb);
  b.show(argc,argv);
  return Fl::run();
}
