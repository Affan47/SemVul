ReceiveCommand(int * player, char * cmd) {
  if (SDLNet_UDP_Recv(mySock, packetCmd) != 0) {
    net_command_t * c = (net_command_t*)(packetCmd->data);
    *player = ComputePlayerID(c->id);
    *cmd = c->command;
    return 0;
  }

  return -1;
}
