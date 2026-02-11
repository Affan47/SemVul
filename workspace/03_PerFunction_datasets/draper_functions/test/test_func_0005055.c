createAndSendDocPropCR( const gchar ** pAtts, const gchar ** pProps)
{
	PT_AttrPropIndex indexAP = 0;
	PP_AttrProp * pAP = new PP_AttrProp();
	pAP->setAttributes(pAtts);
	pAP->setProperties(pProps);
	bool b = m_varset.addIfUniqueAP(pAP,&indexAP);
	PX_ChangeRecord * pcr= new PX_ChangeRecord(PX_ChangeRecord::PXT_ChangeDocProp,0,indexAP,0);
	const pf_Frag_Strux * pfStart = static_cast<pf_Frag_Strux *>(getFragments().getFirst());
	m_pDocument->notifyListeners(pfStart, pcr);
	delete pcr;
	return b;
}
