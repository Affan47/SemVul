DrawText(double x, double y, const std::string &text)
  {
    int sx = round(x*m_scale);
    int sy = round(y*m_scale/m_aspect);
    for (int i=0; i<text.size(); ++i) {
      if (sy>=0 && sy<m_height && sx+i>=0 && sx+i<m_width)
        m_buf.at(sy).at(sx+i) = text.at(i);
    }
  }
