Fill(size_t nb)
  {
    std::string towrite = std::string(nb, 0x00);
    this->mp_Stream->write(towrite.c_str(), nb);
    return nb;
  }
