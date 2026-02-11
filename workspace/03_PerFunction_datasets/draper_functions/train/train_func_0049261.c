restoreSockets(dmtcp::DmtcpCoordinatorAPI& coordinatorAPI,
                           dmtcp::ConnectionState& ckptCoord)
{
  JTRACE ("restoreSockets begin");
  jalib::JSocket& restoreSocket = coordinatorAPI.openRestoreSocket();


  coordinatorAPI.connectToCoordinator();
  coordinatorAPI.sendCoordinatorHandshake(jalib::Filesystem::GetProgramName(),
                                          compGroup, numPeers,
                                          DMT_RESTART_PROCESS);
  coordinatorAPI.recvCoordinatorHandshake(&coordTstamp);
  JTRACE("Connected to coordinator") (coordTstamp);

  jalib::JSocket& coordinatorSocket = coordinatorAPI.coordinatorSocket();

  ckptCoord.doReconnect(coordinatorSocket, restoreSocket);

  JTRACE ("sockets restored!");
}
