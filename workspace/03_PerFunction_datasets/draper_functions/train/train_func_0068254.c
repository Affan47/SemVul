KfwumFinishFirmwareImage(struct ipmi_intf * intf,
                                                 tKFWUM_InFirmwareInfo firmInfo)
{
   tKFWUM_Status status = KFWUM_STATUS_OK;
   struct ipmi_rs * rsp;
   struct ipmi_rq req;
   struct KfwumFinishFirmwareDownloadReq thisReq;

   thisReq.versionMaj     = firmInfo.versMajor;
   thisReq.versionMinSub  = ((firmInfo.versMinor <<4) | firmInfo.versSubMinor);
   thisReq.versionSdr     = firmInfo.sdrRev;
   thisReq.reserved       = 0;


   memset(&req, 0, sizeof(req));
   req.msg.netfn = IPMI_NETFN_FIRMWARE;
   req.msg.cmd = KFWUM_CMD_ID_FINISH_FIRMWARE_IMAGE;
   req.msg.data = (unsigned char *) &thisReq;
   req.msg.data_len = 4;

   do
   {
   	rsp = intf->sendrecv(intf, &req);
   }while (rsp->ccode == 0xc0);

   if (!rsp)
   {
      printf("Error in FWUM Firmware Finish Firmware Image Download Command\n");
      status = KFWUM_STATUS_ERROR;
   }
   else if (rsp->ccode)
   {
      printf("FWUM Firmware Finish Firmware Image Download returned %x\n",
                                                                    rsp->ccode);
      status = KFWUM_STATUS_ERROR;
   }

   return status;
}
