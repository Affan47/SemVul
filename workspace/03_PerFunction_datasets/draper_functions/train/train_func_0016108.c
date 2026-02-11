CopyHeaderToFile(LargeRAWFile_ptr pStreamFile, uint64_t iOffset, bool bIsBigEndian, bool bIsLastBlock) {
  DataBlock::CopyHeaderToFile(pStreamFile, iOffset, bIsBigEndian, bIsLastBlock);

  if (verticesValid) m_n_vertices = vertices.size();
  if (normalsValid) m_n_normals = normals.size();
  if (texcoordsValid) m_n_texcoords  = texcoords.size();
  if (colorsValid) m_n_colors = colors.size();
  if (vertexIValid) m_n_vertex_indices = vIndices.size();
  if (normalIValid) m_n_normal_indices = nIndices.size();
  if (texcoordIValid) m_n_texcoord_indices = tIndices.size();
  if (colorIValid) m_n_color_indices = cIndices.size();

  pStreamFile->WriteData(m_n_vertices,         bIsBigEndian);
  pStreamFile->WriteData(m_n_normals,          bIsBigEndian);
  pStreamFile->WriteData(m_n_texcoords,        bIsBigEndian);
  pStreamFile->WriteData(m_n_colors,           bIsBigEndian);
  pStreamFile->WriteData(m_n_vertex_indices,   bIsBigEndian);
  pStreamFile->WriteData(m_n_normal_indices,   bIsBigEndian);
  pStreamFile->WriteData(m_n_texcoord_indices, bIsBigEndian);
  pStreamFile->WriteData(m_n_color_indices,    bIsBigEndian);
  pStreamFile->WriteData(m_DefaultColor[0],    bIsBigEndian);
  pStreamFile->WriteData(m_DefaultColor[1],    bIsBigEndian);
  pStreamFile->WriteData(m_DefaultColor[2],    bIsBigEndian);
  pStreamFile->WriteData(m_DefaultColor[3],    bIsBigEndian);
  pStreamFile->WriteData(uint64_t(m_Desc.size()),bIsBigEndian);
  pStreamFile->WriteData(m_Desc);
  pStreamFile->WriteData(m_PolySize          , bIsBigEndian);
}
