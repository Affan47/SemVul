isDefaultGateway() const
{
   return(NetworkInterface::defaultGatewayInfo().interfaceName().compare(m_strName) == 0);
}
