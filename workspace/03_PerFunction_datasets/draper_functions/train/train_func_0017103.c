reloadFont(GR_CairoGraphics * pG)
{
	UT_return_if_fail( pG );

	UT_uint32 iZoom = pG->getZoomPercentage();
	if(m_pf && (m_bGuiFont || m_iZoom == iZoom))
		return;

	m_iZoom = iZoom;

	UT_DEBUGMSG(("GR_PangoFont::reloadFont() zoom %% %d\n", iZoom));

	UT_LocaleTransactor t(LC_NUMERIC, "C");
 	std::string sLay;
 	std::string sDev;
	if(!m_bGuiFont && pG->queryProperties(GR_Graphics::DGP_SCREEN))
 	{
 		sDev = UT_std_string_sprintf("%s %f", m_sDesc.c_str(), m_dPointSize * (double)m_iZoom / 100.0);
 		sLay = UT_std_string_sprintf("%s %f", m_sLayoutDesc.c_str(), m_dPointSize);
 	}
	else
 	{
 		sDev = UT_std_string_sprintf("%s %f", m_sDesc.c_str(), m_dPointSize);
 		sLay = UT_std_string_sprintf("%s %f", m_sLayoutDesc.c_str(), m_dPointSize);
 	}

 	if(m_pfdLay)
  	{
 		pango_font_description_free(m_pfdLay);
 		m_pfdLay = NULL;
  	}


 	if(m_pfdDev)
 	{
 		pango_font_description_free(m_pfdDev);
 		m_pfdDev = NULL;
 	}

 	m_pfdLay = pango_font_description_from_string(sLay.c_str());
 	UT_return_if_fail(m_pfdLay);

 	m_pfdDev = pango_font_description_from_string(sDev.c_str());
 	UT_return_if_fail(m_pfdDev);

	if (m_pf) {
		g_object_unref(m_pf);
	}
	m_pf = pango_context_load_font(pG->getContext(), m_pfdDev);
	if(m_pLayoutF) {
		g_object_unref(m_pLayoutF);
	}
	m_pLayoutF = pango_context_load_font(pG->getLayoutContext(), m_pfdLay);

	UT_return_if_fail( m_pf );
 	UT_return_if_fail( m_pLayoutF );

 	PangoFontMetrics * pfm = pango_font_get_metrics(m_pLayoutF, m_pPLang);
	UT_return_if_fail( pfm);


 	m_iAscent = (UT_uint32) pango_font_metrics_get_ascent(pfm)/PANGO_SCALE;
 	m_iDescent = (UT_uint32) pango_font_metrics_get_descent(pfm)/PANGO_SCALE;
	UT_DEBUGMSG(("metrics asc %d desc %d\n", m_iAscent, m_iDescent));

 	xxx_UT_DEBUGMSG(("Layout Font Ascent %d point size %f zoom %d \n",m_iAscent, m_dPointSize, m_iZoom));
	pango_font_metrics_unref(pfm);

	UT_return_if_fail( pfm);
}
