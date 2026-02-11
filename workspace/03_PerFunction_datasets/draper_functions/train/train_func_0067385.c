Reset() {

  if (reloc_iterator_ != NULL) delete reloc_iterator_;
  if (reloc_iterator_original_ != NULL) delete reloc_iterator_original_;
  reloc_iterator_ = new RelocIterator(debug_info_->code());
  reloc_iterator_original_ = new RelocIterator(debug_info_->original_code());


  break_point_ = -1;
  position_ = 1;
  statement_position_ = 1;
  Next();
}
