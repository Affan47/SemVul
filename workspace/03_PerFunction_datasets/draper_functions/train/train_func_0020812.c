FCEUNET_SendCommand(uint8 cmd, uint32 len)
{
 uint8 buf[numlocal + 1 + 4];

 buf[0] = 0xFF;
 FCEU_en32lsb(&buf[numlocal], len);
 buf[numlocal + 4] = cmd;
 #ifdef NETWORK
 if(!FCEUD_SendData(buf,numlocal + 1 + 4))
 {
  NetError();
  return(0);
 }
 #endif
 return(1);
}
