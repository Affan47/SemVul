ImeUpdateOpenArea(struct ipmi_intf *intf)
{
   struct ipmi_rs * rsp;
   struct ipmi_rq req;
   uint8_t buffer[ 2 ];

   #ifdef OUTPUT_DEBUG
   printf("ImeUpdateOpenArea\n");
   #endif

   memset(&req, 0, sizeof(req));
   req.msg.netfn = 0x30;
   req.msg.cmd = 0xA1;

   buffer[0] = 0x01;
   buffer[1] = 0x00;
   req.msg.data = buffer;

   req.msg.data_len = 2;

   rsp = intf->sendrecv(intf, &req);
   if (rsp == NULL) {
      lprintf(LOG_ERR, "UpdateOpenArea command failed");
      return IME_ERROR;
   }
   if (rsp->ccode > 0) {
      lprintf(LOG_ERR, "UpdateOpenArea command failed: %s",
         val2str(rsp->ccode, completion_code_vals));
      return IME_ERROR;
   }

   lprintf(LOG_DEBUG, "UpdateOpenArea command succeed");
   return IME_SUCCESS;
}
