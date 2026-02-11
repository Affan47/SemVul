kf_paste() {
  if (readonly()) { fl_beep(); return 1; }
  Fl::paste(*this, 1);
  return 1;
}
