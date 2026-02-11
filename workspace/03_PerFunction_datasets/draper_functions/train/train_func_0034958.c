UnregisterClients(void)
{
  if (m_cec && m_cec->IsRunning())
    m_cec->UnregisterClients();

  m_clients.clear();

  DELETE_AND_NULL(m_client);
}
