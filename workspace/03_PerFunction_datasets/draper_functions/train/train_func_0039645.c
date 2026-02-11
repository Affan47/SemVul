Dot4Credit(mud_channel *pc, int fd, unsigned short credit)
{
   mud_device *pd = &msp->device[pc->dindex];
   unsigned char buf[HPMUD_BUFFER_SIZE];
   int stat=0, len, n;
   DOT4Credit *pCmd;
   DOT4CreditReply *pReply;

   memset(buf, 0, sizeof(DOT4Credit));
   pCmd = (DOT4Credit *)buf;
   n = sizeof(DOT4Credit);
   pCmd->h.length = htons(n);
   pCmd->h.credit = 1;
   pCmd->cmd = DOT4_CREDIT;
   pCmd->psocket = pc->sockid;
   pCmd->ssocket = pc->sockid;
   pCmd->credit = htons(credit);

   if ((len = (pd->vf.write)(fd, pCmd, n, HPMUD_EXCEPTION_TIMEOUT)) != n)
   {
      BUG("unable to write Dot4Credit: %m\n");
      stat = 1;
      goto bugout;
   }

   stat = Dot4ReverseReply(pc, fd, buf, sizeof(buf));
   pReply = (DOT4CreditReply *)buf;

   if ((stat != 0) || (pReply->cmd != (0x80 | DOT4_CREDIT)) || (pReply->result != 0))
   {
      BUG("invalid Dot4CreditReply: cmd=%x, result=%x\n", pReply->cmd, pReply->result);
      stat = 1;
      goto bugout;
   }

   pc->ta.p2hcredit += credit;

bugout:
   return stat;
}
