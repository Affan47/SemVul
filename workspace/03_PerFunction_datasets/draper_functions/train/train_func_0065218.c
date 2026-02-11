InsertScanbeam(const long64 Y)
{
  if( !m_Scanbeam )
  {
    m_Scanbeam = new Scanbeam;
    m_Scanbeam->next = 0;
    m_Scanbeam->Y = Y;
  }
  else if(  Y > m_Scanbeam->Y )
  {
    Scanbeam* newSb = new Scanbeam;
    newSb->Y = Y;
    newSb->next = m_Scanbeam;
    m_Scanbeam = newSb;
  } else
  {
    Scanbeam* sb2 = m_Scanbeam;
    while( sb2->next  && ( Y <= sb2->next->Y ) ) sb2 = sb2->next;
    if(  Y == sb2->Y ) return;
    Scanbeam* newSb = new Scanbeam;
    newSb->Y = Y;
    newSb->next = sb2->next;
    sb2->next = newSb;
  }
}
