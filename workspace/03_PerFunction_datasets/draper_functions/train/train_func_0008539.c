calcForces()
{

  Vec3 D=m_p1->getPos()-m_p2->getPos();
  double dist_sq=D*D;

  double cut_dist=m_cutoff*(m_p1->getRad()+m_p2->getRad());
  if(dist_sq<(cut_dist*cut_dist)){

    Vec3 dvel=m_p1->getVel()-m_p2->getVel();

    Vec3 eps_dot=dvel/sqrt(dist_sq);
    m_force=eps_dot*m_damp*m_cross_section;

    m_p2->applyForce(m_force,m_p2->getPos());
    m_p1->applyForce(-1.0*m_force,m_p1->getPos());
  }
  m_cpos=(m_p1->getPos()+m_p2->getPos())*0.5;
}
