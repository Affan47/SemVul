border(const Color& col, const length& len) const
  {
    return pen_line(pen_data(col, len), Xfine(), m_border);
  }
