connectToServer()
{
   m_pSocket->abort();
   m_pSocket->connectToServer(KEY);
}
