GetMaxVertexId() const
  {
    int maxId = -1;
    for (size_t i = 0 ; i < this->m_Vertices.size() ; ++i)
    {
      if (this->m_Vertices[i].m_Id > maxId)
        maxId = this->m_Vertices[i].m_Id;
    };
    return maxId;
  }
