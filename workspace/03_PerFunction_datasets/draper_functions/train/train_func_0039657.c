add(P F(double, double), const domain& R)
  {
    scenery tmp(F, R);
    (*this).m_data.merge(tmp.m_data, by_distance());

    return *this;
  }
