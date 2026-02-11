HpmfwupgQuerySelftestResult(struct ipmi_intf *intf, struct HpmfwupgQuerySelftestResultCtx* pCtx,
                                struct HpmfwupgUpgradeCtx* pFwupgCtx)
{
   int    rc = HPMFWUPG_SUCCESS;
   struct ipmi_rs * rsp;
   struct ipmi_rq   req;
   unsigned char selfTestTimeout = 0;
   unsigned int  timeoutSec1, timeoutSec2;

   pCtx->req.picmgId = HPMFWUPG_PICMG_IDENTIFIER;


   if ( pFwupgCtx != NULL )
   {

      struct HpmfwupgImageHeader* pImageHeader = (struct HpmfwupgImageHeader*)
                                                         pFwupgCtx->pImageData;
      selfTestTimeout = pImageHeader->selfTestTimeout;
   }
   else
   {
      selfTestTimeout = HPMFWUPG_DEFAULT_UPGRADE_TIMEOUT;
   }

   memset(&req, 0, sizeof(req));
   req.msg.netfn    = IPMI_NETFN_PICMG;
	req.msg.cmd      = HPMFWUPG_QUERY_SELFTEST_RESULT;
	req.msg.data     = (unsigned char*)&pCtx->req;
	req.msg.data_len = sizeof(struct HpmfwupgQuerySelftestResultReq);


   timeoutSec1 = time(NULL);
   timeoutSec2 = time(NULL);
   do
   {

      usleep(100000);
      rsp = HpmfwupgSendCmd(intf, req, pFwupgCtx);


      if ( rsp )
      {
         if ( HPMFWUPG_IS_RETRYABLE(rsp->ccode) )
         {
            lprintf(LOG_DEBUG,"HPM: [PATCH]Retryable error detected");
            rsp->ccode = HPMFWUPG_COMMAND_IN_PROGRESS;
         }
      }
      timeoutSec2 = time(NULL);

   }while( rsp &&
          (rsp->ccode == HPMFWUPG_COMMAND_IN_PROGRESS) &&
          (timeoutSec2 - timeoutSec1 < selfTestTimeout ) );

   if ( rsp )
   {
      if ( rsp->ccode == 0x00 )
      {
         memcpy(&pCtx->resp, rsp->data, sizeof(struct HpmfwupgQuerySelftestResultResp));
         if ( verbose )
         {
            lprintf(LOG_NOTICE,"Self test results:");
            lprintf(LOG_NOTICE,"Result1 = %x", pCtx->resp.result1);
            lprintf(LOG_NOTICE,"Result2 = %x", pCtx->resp.result2);
         }
      }
      else
      {
         lprintf(LOG_NOTICE,"Error getting self test results");
         lprintf(LOG_NOTICE,"compcode=0x%x: %s",
		rsp->ccode,
		val2str(rsp->ccode, completion_code_vals));
         rc = HPMFWUPG_ERROR;
      }
   }
   else
   {
       lprintf(LOG_NOTICE,"Error getting upgrade status\n");
       rc = HPMFWUPG_ERROR;
   }

   return rc;
}
