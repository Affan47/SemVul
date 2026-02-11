compare(Fl_Shared_Image **i0,
                         Fl_Shared_Image **i1) {
  int i = strcmp((*i0)->name(), (*i1)->name());

  if (i) return i;
  else if (((*i0)->w() == 0 && (*i1)->original_) ||
           ((*i1)->w() == 0 && (*i0)->original_)) return 0;
  else if ((*i0)->w() != (*i1)->w()) return (*i0)->w() - (*i1)->w();
  else return (*i0)->h() - (*i1)->h();
}
