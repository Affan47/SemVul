bnet_sig_to_ascii(BSOCK * bs)
{
   static char buf[30];
   switch (bs->msglen) {
   case BNET_EOD:
      return "BNET_EOD";
   case BNET_EOD_POLL:
      return "BNET_EOD_POLL";
   case BNET_STATUS:
      return "BNET_STATUS";
   case BNET_TERMINATE:
      return "BNET_TERMINATE";
   case BNET_POLL:
      return "BNET_POLL";
   case BNET_HEARTBEAT:
      return "BNET_HEARTBEAT";
   case BNET_HB_RESPONSE:
      return "BNET_HB_RESPONSE";
   case BNET_SUB_PROMPT:
      return "BNET_SUB_PROMPT";
   case BNET_TEXT_INPUT:
      return "BNET_TEXT_INPUT";
   default:
      sprintf(buf, _("Unknown sig %d"), (int)bs->msglen);
      return buf;
   }
}
