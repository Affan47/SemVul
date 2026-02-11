OnDestroy()
{

	if (m_thread)
	{
		m_stop = true;
		g_thread_join(m_thread);
		m_thread = NULL;
	}

	CDialog::OnDestroy();
}
