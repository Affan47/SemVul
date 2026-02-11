SetActive(int direction)
{
	if (m_pControlSocket)
		m_pControlSocket->SetAlive();

	if (!m_activeStatus[direction])
		AddNotification(new CActiveNotification(direction));
	m_activeStatus[direction] = 2;
}
