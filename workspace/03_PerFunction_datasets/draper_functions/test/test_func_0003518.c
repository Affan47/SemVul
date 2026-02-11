makeEmbedView(AD_Document * pDoc, UT_uint32  api, const char * szDataID)
{
  GR_EmbedView * pEmV= new GR_EmbedView(pDoc,api);
  m_vecSnapshots.addItem(pEmV);
  UT_sint32 iNew = m_vecSnapshots.getItemCount()-1;
  pEmV->m_sDataID = szDataID;
  pEmV->getSnapShots();
  pEmV->m_iZoom = getGraphics()->getZoomPercentage();
  return iNew;
}
