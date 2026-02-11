NextChar() {


  if (current_char_ == '\n') {
    ++line_;
    column_ = 0;
  } else if (current_char_ == '\t') {
    column_ += kTabWidth - column_ % kTabWidth;
  } else {
    ++column_;
  }


  ++buffer_pos_;
  if (buffer_pos_ < buffer_size_) {
    current_char_ = buffer_[buffer_pos_];
  } else {
    Refresh();
  }
}
