GetOrientationTypeMSLR(WordsRange currRange) const
{
  if (m_first) {
    if (currRange.GetStartPos() == 0) {
      return M;
    } else {
      return DR;
    }
  }
  if (m_prevRange.GetEndPos() == currRange.GetStartPos()-1) {
    return M;
  } else if (m_prevRange.GetStartPos() == currRange.GetEndPos()+1) {
    return S;
  } else if (m_prevRange.GetEndPos() < currRange.GetStartPos()) {
    return DR;
  }
  return DL;
}
