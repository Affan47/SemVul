seen_through(const Camera& mycam) const
  {
    Color col(m_color);
    if (!col.is_unset())
      col = mycam(col);

    return pen_data(col, m_width);
  }
