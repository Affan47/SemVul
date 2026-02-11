fogModeMess(int mode)
{
  switch (mode)
    {
    case 0 :
      GemMan::m_fogMode = GemMan::FOG_OFF;
      break;

    case 1 :
      GemMan::m_fogMode = GemMan::FOG_LINEAR;
      break;

    case 2 :
      GemMan::m_fogMode = GemMan::FOG_EXP;
      break;

    case 3 :
      GemMan::m_fogMode = GemMan::FOG_EXP2;
      break;

    default :
      error("fogmode must be 0, 1, 2 or 3");
      break;
    }
}
