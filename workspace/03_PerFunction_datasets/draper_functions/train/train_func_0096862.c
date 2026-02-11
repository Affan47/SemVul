Bind() {
#ifdef DEBUG


  for (int i = 0; i < reaching_frames_.length(); i++) {
    ASSERT(reaching_frames_[i] == NULL ||
           reaching_frames_[i]->height() == expected_height_);
  }
#endif


  if (cgen()->has_valid_frame()) {
    int count = cgen()->frame()->height() - expected_height_;
    cgen()->frame()->ForgetElements(count);
  }
  DoBind();
}
