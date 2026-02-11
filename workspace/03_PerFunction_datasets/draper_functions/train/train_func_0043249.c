ContentInfo(const StreamProperties& p) {
  Packet* pkt = AllocatePacket(sizeof(PVR_STREAM_PROPERTIES));

  if (pkt != NULL) {
    PVR_STREAM_PROPERTIES props;
    props << p;
    SetPacketData(pkt, (uint8_t*)&props, DMX_SPECIALID_STREAMCHANGE, 0, 0);
  }

  return pkt;
}
