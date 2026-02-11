startPage(const char * , UT_uint32 ,
									  bool , UT_uint32 , UT_uint32 )
{
	if (m_bDoShowPage) {
		cairo_show_page(m_cr);
	}

	m_bDoShowPage = true;

	return true;
}
