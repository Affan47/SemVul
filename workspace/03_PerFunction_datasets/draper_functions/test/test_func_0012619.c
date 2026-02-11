AddCommand(const cec_command &command)
{

  for (vector<CCECClient *>::iterator it = m_clients.begin(); it != m_clients.end(); it++)
    (*it)->AddCommand(command);
}
