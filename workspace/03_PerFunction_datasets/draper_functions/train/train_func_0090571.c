GetSourceIndex2PosMap() const
{
  std::set<size_t> sourcePoses;

  CollType::const_iterator iter;
  for (iter = m_collection.begin(); iter != m_collection.end(); ++iter) {
    size_t sourcePos = iter->first;
    sourcePoses.insert(sourcePos);
  }
  std::vector<size_t> ret(sourcePoses.begin(), sourcePoses.end());
  return ret;
}
