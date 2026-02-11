test_shortcut(const char *t, const bool require_alt) {
  if (!t) return 0;

  if (require_alt && Fl::event_state(FL_ALT)==0) return 0;
  unsigned int c = fl_utf8decode(Fl::event_text(), Fl::event_text()+Fl::event_length(), 0);
#ifdef __APPLE__


  if (c && Fl::event_state(FL_ALT))
    c = Fl::event_key();
#endif
  if (!c) return 0;
  unsigned int ls = label_shortcut(t);
  if (c == ls)
    return 1;
#ifdef __APPLE__

  if (Fl::event_state(FL_ALT) && c<128 && isalpha(c) && (unsigned)toupper(c)==ls)
    return 1;
#endif
  return 0;
}
