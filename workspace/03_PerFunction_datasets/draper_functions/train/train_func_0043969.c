_getLayoutPropFromObject(const char * szProp)
{
  PT_AttrPropIndex api = getBlock()->getDocument()->getAPIFromSOH(m_OH);
  const PP_AttrProp * pAP = NULL;
  const char * szPropVal = NULL;
  getBlock()->getDocument()->getAttrProp(api, &pAP);
  if(pAP)
    {
      bool bFound = pAP->getProperty(szProp, szPropVal);
      if(bFound)
	{
	  return atoi(szPropVal);
	}
    }
  return -1;
}
