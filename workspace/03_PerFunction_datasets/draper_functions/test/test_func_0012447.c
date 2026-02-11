getDirtyRegion(int buffer)
{
  if (buffer < 0) buffer = m_app ? m_app->renderer()->activeBuffer() : 0;
  return m_dirty[buffer];
}
