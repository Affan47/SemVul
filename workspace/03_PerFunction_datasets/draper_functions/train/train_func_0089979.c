integrate(double dt)
{
  if(m_is_dynamic){
    if (getDo2dCalculations()) {
      m_force = Vec3(m_force.X(), m_force.Y(), 0);
    }
#if 1

    m_vel+=m_force*m_div_mass*dt;
    m_pos+=m_vel*dt;
#else

    const Vec3  Acc = m_force*m_div_mass ;
    m_pos +=  dt*m_vel + 0.5*dt*dt*Acc ;
    m_vel +=  dt*Acc;
#endif
  }
}
