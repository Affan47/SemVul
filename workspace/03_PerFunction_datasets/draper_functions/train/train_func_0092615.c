kf_delete_word_left() {
  if (readonly()) { fl_beep(); return 1; }
  if (mark() != position()) return cut();
  cut(word_start(position()), position());
  return 1;
}
