EndToken() {


  if (buffer_pos_ != token_start_) {
    current_.text.append(buffer_ + token_start_, buffer_pos_ - token_start_);
  }
  token_start_ = -1;
}
