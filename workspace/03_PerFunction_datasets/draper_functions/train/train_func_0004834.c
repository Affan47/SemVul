operator>><std::string>(std::string& n) {

    uint16_t		size = 0;

    (*this) >> size;
    ByteArray::iterator it = this->begin();
    if (this->size() >= size)
      for (; size; --size) {
	n += *it;
	it = this->erase(it);
      }
    return (*this);
  }
