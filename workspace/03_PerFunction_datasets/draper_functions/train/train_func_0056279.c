fogDensityMess(float val)
{
  if (val < 0.f)
    val = 0.f;

  GemMan::m_fog = val;
}
