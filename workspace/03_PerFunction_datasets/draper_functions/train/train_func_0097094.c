Clear(void)
{
  if(META_DEBUG) METAIO_STREAM::cout << "MetaBlob: Clear" << METAIO_STREAM::endl;
  MetaObject::Clear();
  if(META_DEBUG) METAIO_STREAM::cout << "MetaBlob: Clear: m_NPoints" << METAIO_STREAM::endl;

  PointListType::iterator it = m_PointList.begin();
  while(it != m_PointList.end())
  {
    BlobPnt* pnt = *it;
    it++;
    delete pnt;
  }
  m_PointList.clear();
  m_NPoints = 0;
  strcpy(m_PointDim, "x y z red green blue alpha");
  m_ElementType = MET_FLOAT;
}
