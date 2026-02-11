MlcReverseCmd(mud_channel *pc, int fd)
{
   mud_device *pd = &msp->device[pc->dindex];
   unsigned char buf[HPMUD_BUFFER_SIZE];
   int stat=0, len, size;
   unsigned int pklen;
   unsigned char *pBuf;
   MLCReply *pPk;

   pPk = (MLCReply *)buf;

   pBuf = buf;


   size = sizeof(MLCHeader);
   while (size > 0)
   {
      if ((len = (pd->vf.read)(fd, pBuf, size, HPMUD_EXCEPTION_TIMEOUT)) < 0)
      {
         BUG("unable to read MlcReverseCmd header: %m\n");
         stat = 1;
         goto bugout;
      }
      size-=len;
      pBuf+=len;
   }


   if ((pklen = ntohs(pPk->h.length)) > sizeof(buf))
   {
      BUG("invalid MlcReverseCmd packet size: size=%d\n", pklen);
      stat = 1;
      goto bugout;
   }


   size = pklen - sizeof(MLCHeader);
   while (size > 0)
   {
      if ((len = (pd->vf.read)(fd, pBuf, size, HPMUD_EXCEPTION_TIMEOUT)) < 0)
      {
         BUG("unable to read MlcReverseCmd data: %m\n");
         stat = 1;
         goto bugout;
      }
      size-=len;
      pBuf+=len;
   }

   stat = MlcExecReverseCmd(pc, fd, buf);

bugout:
   return stat;
}
