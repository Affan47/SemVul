MessageSetByteSize() const {
  int total_size = 0;

  for (map<int, Extension>::const_iterator iter = extensions_.begin();
       iter != extensions_.end(); ++iter) {
    total_size += iter->second.MessageSetItemByteSize(iter->first);
  }

  return total_size;
}
