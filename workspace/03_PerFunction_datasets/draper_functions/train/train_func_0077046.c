ooCreateH225Connection(OOH323CallData *call)
{
   int ret=0, i;
   OOSOCKET channelSocket=0;
   for (i=0;i<3;i++) {
   if((ret=ooSocketCreate (&channelSocket, call->versionIP))!=ASN_OK)
   {
      OOTRACEERR3("Failed to create socket for transmit H2250 channel (%s, %s)"
                  "\n", call->callType, call->callToken);
      if(call->callState < OO_CALL_CLEAR)
      {
         call->callState = OO_CALL_CLEAR;
         call->callEndReason = OO_REASON_TRANSPORTFAILURE;
      }
      return OO_FAILED;
   }
   else
   {


#ifndef _WIN32
      ret = ooBindPort(OOTCP,channelSocket, call->localIP);
#else
      ret = ooBindOSAllocatedPort(channelSocket, call->localIP);
#endif

      if(ret == OO_FAILED)
      {
         OOTRACEERR3("Error:Unable to bind to a TCP port (%s, %s)\n",
         call->callType, call->callToken);
         if(call->callState < OO_CALL_CLEAR)
         {
            call->callState = OO_CALL_CLEAR;
            call->callEndReason = OO_REASON_TRANSPORTFAILURE;
         }
         return OO_FAILED;
      }

      if (0 == call->pH225Channel) {
         call->pH225Channel =
            (OOH323Channel*) memAllocZ (call->pctxt, sizeof(OOH323Channel));
      }
      call->pH225Channel->port = ret;

      OOTRACEINFO6("Trying to connect to remote endpoint(%s:%d) (IPv%d) to setup "
                   "H2250 channel (%s, %s)\n", call->remoteIP,
                   call->remotePort, call->versionIP, call->callType, call->callToken);

      if((ret=ooSocketConnect(channelSocket, call->remoteIP,
                              call->remotePort))==ASN_OK)
      {
         call->pH225Channel->sock = channelSocket;

         OOTRACEINFO3("H2250 transmiter channel creation - successful "
                      "(%s, %s)\n", call->callType, call->callToken);


         if(!strcmp(call->localIP, "0.0.0.0") || !strcmp(call->localIP, "::"))
         {
            OOTRACEDBGA3("Determining IP address for outgoing call in "
                         "multihomed mode. (%s, %s)\n", call->callType,
                          call->callToken);
            ret = ooSocketGetIpAndPort(channelSocket, call->localIP, 2+8*4+7,
                                       &call->pH225Channel->port, NULL);
            if(ret != ASN_OK)
            {
               OOTRACEERR3("ERROR:Failed to retrieve local ip and port from "
                           "socket for multihomed mode.(%s, %s)\n",
                            call->callType, call->callToken);
               if(call->callState < OO_CALL_CLEAR)
               {
                  call->callState = OO_CALL_CLEAR;
                  call->callEndReason = OO_REASON_TRANSPORTFAILURE;
               }
               return OO_FAILED;
            }
            OOTRACEDBGA4("Using local ip %s for outgoing call(multihomedMode)."
                         " (%s, %s)\n", call->localIP, call->callType,
                         call->callToken);
         }
         return OO_OK;
      }
      else
      {
         OOTRACEERR5("ERROR:Failed to connect to remote destination for "
                    "transmit H2250 channel(%s, %s, %d, %s)\n",call->callType,
                     call->callToken, channelSocket, call->localIP);
	 close(channelSocket);

         if(call->callState < OO_CALL_CLEAR)
         {
            call->callState = OO_CALL_CLEAR;
            call->callEndReason = OO_REASON_NOUSER;
         }
         if (i>=2) return OO_FAILED; else continue;
      }

      return OO_FAILED;
    }
  }
  return OO_FAILED;
}
