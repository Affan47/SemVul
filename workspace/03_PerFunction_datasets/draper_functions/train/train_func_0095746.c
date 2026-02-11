GetComments(int start, int end, vector<StringPiece> *ranges) {


  if (!comments_) {
    return;
  }


  for (vector<StringPiece>::const_iterator it = comments_->begin();
       it != comments_->end(); ++it) {
    if ((it->data() >= data_.c_str() + start &&
         it->data() + it->size() <= data_.c_str() + end)) {
      ranges->push_back(*it);
    }
  }
}
