BrickSize(const ExtendedOctree& tree,
                                            uint64_t index) {


  if(tree.m_vTOC[index].m_eCompression != CT_NONE) {

    return tree.ComputeBrickSize(tree.IndexToBrickCoords(index)).volume() *
           tree.GetComponentTypeSize() *
           tree.GetComponentCount();
  }
  return tree.m_vTOC[index].m_iLength;
}
