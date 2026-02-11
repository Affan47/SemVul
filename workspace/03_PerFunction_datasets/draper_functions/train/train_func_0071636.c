operator[](PayloadRawInterface::Size_t pos) const {
  if(!((PayloadHTTPOutRaw&)(*this)).remake_header(false)) return 0;
  if(pos == -1) pos = 0;
  if(pos < 0) return 0;
  if(pos < header_.length()) {
    return header_[pos];
  };
  pos -= header_.length();
  if(rbody_) {
    return rbody_->operator[](pos);
  };
  if(sbody_) {

  };
  return 0;
}
