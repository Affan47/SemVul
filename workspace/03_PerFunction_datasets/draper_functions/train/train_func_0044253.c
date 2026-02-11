extract(ByteArray& data, size_t len, size_t pos) {

    ByteArray::iterator it(this->begin() + pos);

    for (size_t i = 0; i < len && it != this->end(); ++i)
      {
	data.push_back(*it);
	it = this->erase(it);
      }
  }
