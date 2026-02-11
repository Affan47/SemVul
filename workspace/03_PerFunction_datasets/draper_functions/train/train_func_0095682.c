PopFrame() {
  size_t prev_size = pxmlnsDepthStack_->back();
  pxmlnsDepthStack_->pop_back();
  if (prev_size < pxmlnsStack_->size()) {
    pxmlnsStack_->erase(pxmlnsStack_->begin() + prev_size,
                        pxmlnsStack_->end());
  }
}
