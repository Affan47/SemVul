useSecureConnection(DcmTransportLayer *tlayer)
{
  OFCondition cond = ASC_setTransportLayer(m_net, tlayer, OFFalse );
  if (cond.good())
    cond = ASC_setTransportLayerType(m_params, OFTrue );
  return cond;
}
