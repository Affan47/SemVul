GetSocketID(int fd, const char *serviceName)
{

   int len = sizeof(cmdHeader_t) + strlen(serviceName);
   char buf[100];
   unsigned char rBuf[100];
   int rd;
   cmdHeader_t *cmd = (cmdHeader_t*)buf;
   cmd->psid     = 0;
   cmd->ssid     = 0;
   cmd->lengthH  = 0;
   cmd->lengthL  = len & 0xff;
   cmd->credit   = 1;
   cmd->control  = 0;
   cmd->command  = 0x09;
   strcpy(buf + sizeof(cmdHeader_t), serviceName);

   rd = sendReceiveCmd(fd, (unsigned char*)buf, len, rBuf, len + 2, 0);
   if ( rd > 0 )
   {
      return rBuf[8];
   }
   else
   {
      return 0;
   }
}
