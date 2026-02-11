MlcCreditRequest(mud_channel *pc, int fd, unsigned short credit)
{
   mud_device *pd = &msp->device[pc->dindex];
   unsigned char buf[HPMUD_BUFFER_SIZE];
   int stat=0, len, n;
   MLCCreditRequest *pCmd;
   MLCCreditRequestReply *pReply;

   memset(buf, 0, sizeof(MLCCreditRequest));
   pCmd = (MLCCreditRequest *)buf;
   n = sizeof(MLCCreditRequest);
   pCmd->h.length = htons(n);
   pCmd->cmd = MLC_CREDIT_REQUEST;
   pCmd->hsocket = pc->sockid;
   pCmd->psocket = pc->sockid;
   pCmd->credit = htons(credit);

   if ((len = (pd->vf.write)(fd, pCmd, n, HPMUD_EXCEPTION_TIMEOUT)) != n)
   {
      BUG("unable to write MlcCreditRequest: %m\n");
      stat = 1;
      goto bugout;
   }

   stat = MlcReverseReply(pc, fd, buf, sizeof(buf));
   pReply = (MLCCreditRequestReply *)buf;

   if ((stat != 0) || (pReply->cmd != (0x80 | MLC_CREDIT_REQUEST)) || (pReply->result != 0))
   {
      BUG("invalid MlcCreditRequestReply: cmd=%x, result=%x\n", pReply->cmd, pReply->result);
      stat = 1;
      goto bugout;
   }

   pc->ta.h2pcredit += ntohs(pReply->credit);

bugout:
   return stat;
}
