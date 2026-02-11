filter(const Color_Base& color)
  {
    Color_Base::RGB_Densities s(color.to_rgb());
    if (Color(color).is_unset())
      s = Color_Base::RGB_Densities(1,1,1);

    m_dens = std::min(m_dens, 1-s.m_dens_green);
    return *this;
  }
