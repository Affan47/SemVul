findProtocolConfig(const QString &_protocol)
{
   SlaveConfigProtocol *scp = protocol.value(_protocol,0);
   if (!scp)
      scp = readProtocolConfig(_protocol);
   return scp;
}
