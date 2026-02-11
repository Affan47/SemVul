calledAETitleAccepted(const OFString & ,
                                     const OFString &calledAE)
{
  if (m_respondWithCalledAETitle)
  {
    return OFTrue;
  }
  if (calledAE != m_aetitle)
    return OFFalse;
  else
    return OFTrue;
}
