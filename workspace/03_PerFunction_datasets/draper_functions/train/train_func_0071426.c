ClearStatus()
{
	if (m_MessageId) {
		gtk_statusbar_pop (GTK_STATUSBAR (m_Bar), m_statusId);
		m_MessageId = 0;
	}
}
