insertAtStrux(PD_Document* pDoc,
										 UT_uint32 res,
										 UT_uint32 iPos,
										 PTStruxType iStruxType,
										 const char* szName)
{
	UT_return_val_if_fail(pDoc, UT_ERROR);
	UT_ASSERT(szName);


   	pDoc->createDataItem(szName, false, m_pbb, getMimeType(), NULL);


    std::string szProps;

	szProps += "width:";
	szProps += UT_convertInchesToDimensionString(DIM_IN, static_cast<double>(m_iWidth)/res, "3.2");
	szProps += "; height:";
	szProps += UT_convertInchesToDimensionString(DIM_IN, static_cast<double>(m_iHeight)/res, "3.2");

	const gchar*	attributes[] = {
		PT_STRUX_IMAGE_DATAID, szName,
		PT_PROPS_ATTRIBUTE_NAME, szProps.c_str(),
	   	NULL, NULL
	};

	pDoc->changeStruxFmt(PTC_AddFmt,iPos,iPos,attributes,NULL,iStruxType);


	return UT_OK;
}
