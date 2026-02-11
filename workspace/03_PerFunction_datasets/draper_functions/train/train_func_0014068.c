SetOrigin(double x, double y, double z)
  {
    if ((this->m_Origin.x() == x)
        && (this->m_Origin.y() == y)
        && (this->m_Origin.z() == z))
      return;
    this->m_Origin.x() = x;
    this->m_Origin.y() = y;
    this->m_Origin.z() = z;
    this->Modified();
  }
