ftpdu_v8_1_swap(struct ftpdu_v8_1 *pdu, int cur)
{
  int16 i;

  i = pdu->count;

#if BYTE_ORDER == LITTLE_ENDIAN
  if (cur == BIG_ENDIAN)
    SWAPINT16(i);
#endif

#if BYTE_ORDER == BIG_ENDIAN
  if (cur == LITTLE_ENDIAN)
    SWAPINT16(i);
#endif

  SWAPINT16(pdu->version);
  SWAPINT16(pdu->count);
  SWAPINT32(pdu->sysUpTime);
  SWAPINT32(pdu->unix_secs);
  SWAPINT32(pdu->unix_nsecs);
  SWAPINT32(pdu->flow_sequence);

  for (--i; i >= 0; --i) {
    SWAPINT32(pdu->records[i].dFlows);
    SWAPINT32(pdu->records[i].dPkts);
    SWAPINT32(pdu->records[i].dOctets);
    SWAPINT32(pdu->records[i].First);
    SWAPINT32(pdu->records[i].Last);
    SWAPINT16(pdu->records[i].src_as);
    SWAPINT16(pdu->records[i].dst_as);
    SWAPINT16(pdu->records[i].input);
    SWAPINT16(pdu->records[i].output);
  }

}
