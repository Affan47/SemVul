ooGetNextPort (OOH323PortType type)
{
   if(type==OOTCP)
   {
      if(gH323ep.tcpPorts.current <= gH323ep.tcpPorts.max)
         return gH323ep.tcpPorts.current++;
      else
      {
         gH323ep.tcpPorts.current = gH323ep.tcpPorts.start;
         return gH323ep.tcpPorts.current++;
      }
   }
   if(type==OOUDP)
   {
      if(gH323ep.udpPorts.current <= gH323ep.udpPorts.max)
         return gH323ep.udpPorts.current++;
      else
      {
         gH323ep.udpPorts.current = gH323ep.udpPorts.start;
         return gH323ep.udpPorts.current++;
      }
   }
   if(type==OORTP)
   {
      if(gH323ep.rtpPorts.current <= gH323ep.rtpPorts.max)
         return gH323ep.rtpPorts.current++;
      else
      {
         gH323ep.rtpPorts.current = gH323ep.rtpPorts.start;
         return gH323ep.rtpPorts.current++;
      }
   }
   return OO_FAILED;
}
