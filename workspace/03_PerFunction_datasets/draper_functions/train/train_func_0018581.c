onPtpInterfaceIsUpAnRunning(NetworkInterface interface)
{


   if (m_pState->isState(ConnectionState::Connecting) || m_pState->isState(ConnectionState::NotConnected))
   {
      const QString strConnectionName(ConnectionManager::connectionName(interface, 5));
      if (!strConnectionName.isNull())
         connected(strConnectionName, interface);
   }


}
