get_color(unsigned i, unsigned j) const
  {
    if (i >= h || j >= w)
      return INVALID_SITE;
    return tab[i][j].m.color;
  }
