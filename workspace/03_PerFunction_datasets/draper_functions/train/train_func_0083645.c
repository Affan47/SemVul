fogRangeMess(float start, float end)
{
  if (start < 0.f)
    start= 0.f;

  if (end < 0.f)
    end  = 0.f;

  GemMan::m_fogStart = start;
  GemMan::m_fogEnd = end;
}
