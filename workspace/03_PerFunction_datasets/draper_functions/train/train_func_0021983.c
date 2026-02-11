HpmfwupgUploadFirmwareBlock(struct ipmi_intf *intf, struct HpmfwupgUploadFirmwareBlockCtx* pCtx,
                                struct HpmfwupgUpgradeCtx* pFwupgCtx, int count
                               ,unsigned int *imageOffset, unsigned int *blockLength )
{
   int rc = HPMFWUPG_SUCCESS;
   struct ipmi_rs * rsp;
   struct ipmi_rq   req;

   pCtx->req.picmgId = HPMFWUPG_PICMG_IDENTIFIER;

   memset(&req, 0, sizeof(req));
   req.msg.netfn    = IPMI_NETFN_PICMG;
   req.msg.cmd      = HPMFWUPG_UPLOAD_FIRMWARE_BLOCK;
   req.msg.data     = (unsigned char*)&pCtx->req;

   req.msg.data_len = 2 + count;

   rsp = HpmfwupgSendCmd(intf, req, pFwupgCtx);

   if ( rsp )
   {
      if ( rsp->ccode == HPMFWUPG_COMMAND_IN_PROGRESS ||
           rsp->ccode == 0x00 )
      {


        if ( rsp->data_len > 1 )
        {


          if ( rsp->data_len == 9 )
          {

             *imageOffset = (rsp->data[4] << 24) + (rsp->data[3] << 16) + (rsp->data[2] << 8) + rsp->data[1];
             *blockLength = (rsp->data[8] << 24) + (rsp->data[7] << 16) + (rsp->data[6] << 8) + rsp->data[5];
          }
          else
          {


              lprintf(LOG_NOTICE,"Error wrong rsp->datalen %d for Upload Firmware block command\n",rsp->data_len);
              rsp->ccode = HPMFWUPG_INT_CHECKSUM_ERROR;
          }
        }
      }

      if ( rsp->ccode == HPMFWUPG_COMMAND_IN_PROGRESS )
      {
         rc = HpmfwupgWaitLongDurationCmd(intf, pFwupgCtx);
      }


      else if ( (rsp->ccode != 0x00) && (rsp->ccode != 0xcc) )
      {


         if ( HPMFWUPG_IS_RETRYABLE(rsp->ccode) )
         {
            lprintf(LOG_DEBUG,"HPM: [PATCH]Retryable error detected");
            rc = HPMFWUPG_UPLOAD_RETRY;
         }


         else if ( rsp->ccode == IPMI_CC_REQ_DATA_INV_LENGTH )
         {
            rc = HPMFWUPG_UPLOAD_BLOCK_LENGTH;
         }
         else
         {
            lprintf(LOG_NOTICE,"Error uploading firmware block, compcode = %x\n",  rsp->ccode);
            rc = HPMFWUPG_ERROR;
         }
      }
   }
   else
   {
      lprintf(LOG_NOTICE,"Error uploading firmware block\n");
      rc = HPMFWUPG_ERROR;
   }

   return rc;
}
