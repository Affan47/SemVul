args(int argc, char **argv) {
  int i; if (Fl::args(argc,argv,i) < argc) Fl::error(helpmsg);
}
