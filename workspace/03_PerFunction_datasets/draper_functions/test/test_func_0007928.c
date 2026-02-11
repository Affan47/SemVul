setSymbols (XAP_Plugin_Registration fnRegister,
							 XAP_Plugin_Registration fnDeregister,
							 XAP_Plugin_VersionCheck fnSupportsVersion)
{
	UT_ASSERT (!m_bLoaded && fnRegister && fnDeregister && fnSupportsVersion);

	if (m_bLoaded || !(fnRegister && fnDeregister && fnSupportsVersion)) return false;

	m_fnRegister = fnRegister;
	m_fnDeregister = fnDeregister;
	m_fnSupportsVersion = fnSupportsVersion;

	m_bLoaded = true;

	return true;
}
