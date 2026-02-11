operator>>=(size_type rs)
{
  if (rs > 0) {
    resize(width_ + rs, height_);
    for (size_type y = 0; y < height_; y++) {
      Cell *c = cells_[y];
      memmove(c + rs, c, (width_ - rs) * sizeof(Cell));
      for (size_type x = 0; x < rs; x++) {
        c[x].character = ' ';
        c[x].attribute = Cell::NONE;
      }
    }
  }
  return *this;
}
