gapCallback(void *data, t_floatarg m_LineGap)
{
  if(m_LineGap<0)m_LineGap=0.f;
  GetMyClass(data)->m_LineGap=(m_LineGap);
  GetMyClass(data)->setPixModified();
}
