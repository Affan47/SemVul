CreditRequest(int fd, unsigned char socketID)
{
   int           rd;
   unsigned char            buf[100];
   unsigned char            rBuf[100];
   cmdHeader_t *cmd = (cmdHeader_t *)buf;
   cmd->psid     = 0;
   cmd->ssid     = 0;
   cmd->lengthH  = 0;
   cmd->lengthL  = 13;
   cmd->credit   = 1;
   cmd->control  = 0;
   cmd->command  = 4;
   buf[sizeof(cmdHeader_t)+0] = socketID;
   buf[sizeof(cmdHeader_t)+1] = socketID;
   buf[sizeof(cmdHeader_t)+2] = 0x00;
   buf[sizeof(cmdHeader_t)+3] = 0x80;
   buf[sizeof(cmdHeader_t)+4] = 0xff;
   buf[sizeof(cmdHeader_t)+5] = 0xff;
   rd = sendReceiveCmd(fd, buf, 13, rBuf, 12, 0);
   if ( rd == 12 )
   {

      return (rBuf[10]*256)+rBuf[11];
   }
   else
   {
      return rd > 0 ? 0 : rd;
   }
}
