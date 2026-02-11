releasePrinterGraphicsContext(GR_Graphics * pGraphics)
{
	UT_UNUSED(pGraphics);
	UT_ASSERT(pGraphics == m_pPrintGraphics);
	DELETEP(m_pPrintGraphics);
	if(m_pPageSetup)
	   g_object_unref(m_pPageSetup);
	m_pPageSetup = NULL;
	if(m_pGtkPageSize)
		gtk_paper_size_free (m_pGtkPageSize);
	m_pGtkPageSize=  NULL;
	if(m_pPO)
		g_object_unref(m_pPO);
	m_pPO=  NULL;
}
