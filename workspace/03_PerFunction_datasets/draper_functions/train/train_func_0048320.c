_setValue(void)
{


  const PP_AttrProp * pAP = NULL;
  getSpanAP(pAP);
  RDFAnchor a( pAP );

  UT_String tmp;


  m_sValue = tmp.c_str();
  return true;
}
