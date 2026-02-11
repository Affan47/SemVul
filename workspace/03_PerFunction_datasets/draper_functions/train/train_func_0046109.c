soapht_read(SANE_Handle handle, SANE_Byte *data, SANE_Int maxLength, SANE_Int *length)
{
   struct soap_session *ps = (struct soap_session *)handle;
   int ret, stat=SANE_STATUS_IO_ERROR;

   DBG8("sane_hpaio_read() handle=%p data=%p maxLength=%d\n", (void *)handle, data, maxLength);
   if(ps->user_cancel)
   {
     DBG8("soapht_read() EVENT_SCAN_CANCEL****uri=%s\n", ps->uri);
     SendScanEvent(ps->uri, EVENT_SCAN_CANCEL);
     return SANE_STATUS_CANCELLED;
   }

   ret = get_ip_data(ps, data, maxLength, length);

   if(ret & (IP_INPUT_ERROR | IP_FATAL_ERROR))
   {
      BUG("ipConvert error=%x\n", ret);
      goto bugout;
   }

   if (ret & IP_DONE)
   {
      stat = SANE_STATUS_EOF;
      SendScanEvent(ps->uri, EVENT_END_SCAN_JOB);
   }
   else
      stat = SANE_STATUS_GOOD;

bugout:
   if (stat != SANE_STATUS_GOOD)
   {
      if (ps->ip_handle)
      {

         ipClose(ps->ip_handle);
         ps->ip_handle = 0;
      }
      ps->bb_end_page(ps, 0);
   }

   DBG8("-sane_hpaio_read() output=%p bytes_read=%d maxLength=%d status=%d\n", data, *length, maxLength, stat);

   return stat;
}
