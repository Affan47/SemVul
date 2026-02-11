unref (const char * href)
{
	if ( href == 0) return;
	if (*href == 0) return;

	bool bInternal = false;
	if (*href == '#') bInternal = true;
	else if (*href != '/') return;

	UT_uint32 index;
	XAP_Resource * match = resource (href, bInternal, &index);
	if (match == 0) return;

	if (match->unref () > 0) return;

	delete m_resource[index];
	m_resource_count--;
	if (index < m_resource_count) m_resource[index] = m_resource[m_resource_count];
}
