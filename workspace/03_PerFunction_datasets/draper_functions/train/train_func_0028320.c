translateBy(const Vec3 &translation)
{

  for(triangle_iterator iter=m_triangles.begin();
      iter!=m_triangles.end();
      iter++){
    iter->move(translation);
  }

  for(edge_iterator iter=m_edges.begin();
      iter!=m_edges.end();
      iter++){
    iter->move(translation);
  }

  for(corner_iterator it = m_corners.begin();
      it != m_corners.end();
      ++it){
    it->move(translation);
  }
}
