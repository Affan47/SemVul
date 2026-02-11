print(Fl_Widget *, void *w) {
  Fl_Widget * g = (Fl_Widget *)w;

  Fl_Printer * p = new Fl_Printer();
  if (!p->start_job(1)) {
    p->start_page();
    p->print_window(g->window());
    p->end_page();
    p->end_job();
  }
  delete p;
}
