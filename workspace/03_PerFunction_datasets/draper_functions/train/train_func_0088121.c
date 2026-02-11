Dot4OpenChannel(mud_channel *pc, int fd)
{
   mud_device *pd = &msp->device[pc->dindex];
   unsigned char buf[HPMUD_BUFFER_SIZE];
   int stat=0, len, n;
   DOT4OpenChannel *pCmd;
   DOT4OpenChannelReply *pReply;

   memset(buf, 0, sizeof(DOT4OpenChannel));
   pCmd = (DOT4OpenChannel *)buf;
   n = sizeof(DOT4OpenChannel);
   pCmd->h.length = htons(n);
   pCmd->h.credit = 1;
   pCmd->cmd = DOT4_OPEN_CHANNEL;
   pCmd->psocket = pc->sockid;
   pCmd->ssocket = pc->sockid;
   pCmd->maxp2s = htons(HPMUD_BUFFER_SIZE);
   pCmd->maxs2p = htons(HPMUD_BUFFER_SIZE);
   pCmd->maxcredit = htons(0xffff);

   if ((len = (pd->vf.write)(fd, pCmd, n, HPMUD_EXCEPTION_TIMEOUT)) != n)
   {
      BUG("unable to write Dot4OpenChannel: %m\n");
      stat = 1;
      goto bugout;
   }

   stat = Dot4ReverseReply(pc, fd, buf, sizeof(buf));
   pReply = (DOT4OpenChannelReply *)buf;

   if ((stat != 0) || (pReply->cmd != (0x80 | DOT4_OPEN_CHANNEL)) || (pReply->result != 0))
   {
      BUG("invalid Dot4OpenChannelReply: cmd=%x, result=%x\n", pReply->cmd, pReply->result);
      stat = 1;
      goto bugout;
   }

   pc->ta.h2psize = ntohs(pReply->maxp2s);
   pc->ta.p2hsize = ntohs(pReply->maxs2p);
   pc->ta.h2pcredit = ntohs(pReply->credit);

bugout:
   return stat;
}
