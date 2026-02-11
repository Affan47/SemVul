wr(const std::shared_ptr<const void>& data,
                    uint64_t offset,
                    size_t len)
{
  if(!this->is_open()) {
    throw std::ios_base::failure("file is not open!");
  }

  if(seeko(this->fp, offset+this->header_size, SEEK_SET) < 0) {
    throw std::ios_base::failure("seek failed!");
  }

  if(fwrite(data.get(), len, 1, this->fp) <= 0) {
    std::ios_base::failure("write failed.");
  }
}
