getCellProperty(PT_DocPosition posCell, const gchar * szPropName, gchar * &szPropValue) const
{
	pf_Frag_Strux* cellSDH;
	bool bres = m_pDoc->getStruxOfTypeFromPosition(posCell,PTX_SectionCell,&cellSDH);
	if(!bres)
	{
		return false;
	}
	m_pDoc->getPropertyFromSDH(cellSDH,isShowRevisions(),getRevisionLevel(),szPropName,const_cast<const char **>(&szPropValue));
	if(szPropValue && *szPropValue)
	{
		return true;
	}
	else
	{
		return false;
	}
}
