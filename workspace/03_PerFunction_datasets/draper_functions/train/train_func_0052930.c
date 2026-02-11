convertFromBuffer(const UT_ByteBuf* pBB,
                                           const std::string& ,
										   UT_sint32 iDisplayWidth,
										   UT_sint32 iDisplayHeight) {
	reset();

	m_data.append(pBB->getPointer(0), pBB->getLength());

	bool forceScale = (iDisplayWidth != -1 && iDisplayHeight != -1);

	gboolean result;

	m_svg = rsvg_handle_new();

	result = rsvg_handle_write(m_svg, pBB->getPointer(0), pBB->getLength(), NULL);
	if (!result) {
		g_object_unref(G_OBJECT(m_svg));
		m_svg = 0;

		return false;
	}

	result = rsvg_handle_close(m_svg, NULL);

	if (!result) {
		g_object_unref(G_OBJECT(m_svg));
		m_svg = 0;

		return false;
	}

	rsvg_handle_get_dimensions(m_svg, &m_size);

	if (!forceScale)
		setupScale(m_size.width, m_size.height);
	else
		setupScale(iDisplayWidth, iDisplayHeight);


	return true;
}
