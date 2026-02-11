notifybandwidth(void)
{
  int i;
  transfer *tr;
  ir_uint64 xdccsent;

  updatecontext();

  if (gdata.exiting) return;
  if (!gdata.maxb) return;

  xdccsent = 0;
  for (i=0; i<XDCC_SENT_SIZE; i++)
    {
      xdccsent += (ir_uint64)gdata.xdccsent[i];
    }
  xdccsent /= 1024;


  if ( (xdccsent*10) > (gdata.maxb*30*9) )
    {
      tr = irlist_get_head(&gdata.trans);
      while(tr)
        {
          notice_slow(tr->nick,"%s bandwidth limit: %2.1f of %2.1fKB/sec used. Your share: %2.1fKB/sec.",
                      (gdata.user_nick ? gdata.user_nick : "??"),
                      ((float)xdccsent)/XDCC_SENT_SIZE,
                      ((float)gdata.maxb)/4.0,
                      tr->lastspeed);
          tr = irlist_get_next(tr);
        }
    }

}
