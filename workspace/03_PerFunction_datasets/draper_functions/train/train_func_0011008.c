RemoveUnusedVertices() {
  RemoveUnusedEntries(m_VertIndices, m_vertices);
  if (!m_NormalIndices.empty()) RemoveUnusedEntries(m_NormalIndices, m_normals);
  if (!m_TCIndices.empty()) RemoveUnusedEntries(m_TCIndices, m_texcoords);
  if (!m_COLIndices.empty()) RemoveUnusedEntries(m_COLIndices, m_colors);
}
