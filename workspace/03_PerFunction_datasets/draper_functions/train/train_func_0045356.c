getHexDump() const
{
  std::stringstream ss;
  ss << "Length=" << length_ << std::endl << std::hex << std::uppercase;
  for(uint32_t index = 0; index < length_; index++) {
    ss << std::setw(2) << std::setfill('0') << uint32_t(buf_[index]) << " ";
    if(!((index+1) % 16)) {
      ss << std::endl;
      continue;
    }
    if(!((index+1) % 8)) {
      ss << " ";
    }
  }
  return ss.str();
}
