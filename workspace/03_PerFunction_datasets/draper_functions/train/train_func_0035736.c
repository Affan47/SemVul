SendKeypress(const cec_logical_address iDestination, const cec_user_control_code key, bool bWait )
{
  CCECBusDevice *dest = m_processor->GetDevice(iDestination);

  return dest ?
      dest->TransmitKeypress(GetPrimaryLogicalAdddress(), key, bWait) :
      false;
}
