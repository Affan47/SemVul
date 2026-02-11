ComputeNonZeroLimits() {
  m_vValueBBox = UINT64VECTOR2(uint64_t(m_pvColorData->size()),0);

  for (size_t i = 0;i<m_pvColorData->size();i++) {
    if ((*m_pvColorData)[i][3] != 0) {
      m_vValueBBox.x = MIN(m_vValueBBox.x, i);
      m_vValueBBox.y = i;
    }
  }
}
