collectStickyNote()
{
  if (m_collecting)
  {
    assert(!m_levelStack.empty());

    m_stickyNotes.push_back(KEYStickyNote(m_levelStack.top().geometry, m_currentText));
    m_levelStack.top().geometry.reset();
    m_currentText.reset();
  }
}
