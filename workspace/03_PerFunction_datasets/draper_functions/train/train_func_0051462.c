CloseChannel(int fd, unsigned char socketID)
{
   unsigned char buf[100];
   int           rd;
   cmdHeader_t *cmd = (cmdHeader_t *)buf;
   cmd->psid     =  0;
   cmd->ssid     =  0;
   cmd->lengthH  =  0;
   cmd->lengthL  = 10;
   cmd->credit   =  1;
   cmd->control  =  0;
   cmd->command  =  2;
   buf[sizeof(cmdHeader_t)+0] = socketID;
   buf[sizeof(cmdHeader_t)+1] = socketID;
   buf[sizeof(cmdHeader_t)+2] = 0;
   rd = sendReceiveCmd(fd, buf,10, buf, 10, 0);
   return rd == 10 ? 1 : rd;
}
