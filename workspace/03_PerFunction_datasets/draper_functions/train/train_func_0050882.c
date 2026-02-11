onCheckPtpInterfaceIsDown()
{
   if (!m_fIsExecuting && m_pState->isState(ConnectionState::Disconnecting))
   {
      const ConnectionInfo connectionInfo(connectionNameOfUpAndRunningPtpInterface());
      if (connectionInfo.first.isNull())
         disConnected();
      else
         connected(connectionInfo.first, connectionInfo.second);
   }
}
