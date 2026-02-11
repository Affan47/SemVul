moveNode(int id,const Vec3& d)
{

  if(id==m_id0) {
    m_p0+=d;
    m_p1-=d;
    m_p2-=d;
  } else if (id==m_id1){
    m_p1+=d;
  } else if (id==m_id2){
    m_p2+=d;
  } else {
    std::cerr << "trying to move node not in triangle!" << std::endl;
  }

  try{
    m_normal=cross(m_p2,m_p1).unit_s();
    m_trans=Matrix3(m_p1,m_p2,m_normal);
    m_invtrans=m_trans.inv();
  }
  catch(VecErr V){
    throw TriangleError();
  }
}
