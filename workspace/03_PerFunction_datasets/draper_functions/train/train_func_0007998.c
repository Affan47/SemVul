Stage3end_terminal_trim (T this) {
  if (this->hittype != TERMINAL) {
    return 0;
  } else {
    return Substring_trim_left(this->substring1) + Substring_trim_right(this->substring1);
  }
}
