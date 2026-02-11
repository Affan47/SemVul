close (void)
{
	#ifdef _LOG_RX_TX
		if (rx_log != NULL)
			fclose(rx_log);
		if (tx_log != NULL)
			fclose(tx_log);
		rx_log = NULL;
		tx_log = NULL;
	#endif
	if (!m_isOpen)
		return m_lastResult = XRV_NOPORTOPEN;

	#ifdef _WIN32
		::FlushFileBuffers(m_handle);


			COMMTIMEOUTS cto;
			::GetCommTimeouts(m_handle,&cto);
			cto.ReadIntervalTimeout = MAXDWORD;
			cto.ReadTotalTimeoutConstant = 0;
			cto.ReadTotalTimeoutMultiplier = 0;
			::SetCommTimeouts(m_handle,&cto);
			char buffer[1024];
			DWORD length;
			do {
				::ReadFile(m_handle, buffer, 1024, &length, NULL);
			} while (length > 0);
		::CloseHandle(m_handle);
	#else
		::close(m_handle);
	#endif
	m_isOpen = false;
	m_endTime = 0;

	return m_lastResult = XRV_OK;
}
