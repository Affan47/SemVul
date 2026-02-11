Save(const std::string& filename) const {
  ofstream file(filename.c_str());

  if (!file.is_open()) return false;


  file << m_iSize.x << " " << m_iSize.y << endl;


  m_Trans1D.Save(file);


  file << m_pvSwatches->size() << endl;


  for (size_t i = 0;i<m_pvSwatches->size();i++) (*m_pvSwatches)[i].Save(file);

  file.close();

  return true;
}
