IsACK(void) const
{
  return packet.size >= 2 ?
      (packet.At(1) & MSGCODE_FRAME_ACK) != 0 :
      false;
}
