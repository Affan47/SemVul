SetForce(Point::Pointer force)
  {
    if (force == this->m_Force)
      return;
    this->m_Force = force;

    this->m_Force->SetType(Point::Force);
    this->Modified();
  }
