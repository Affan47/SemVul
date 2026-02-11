dump_skb (char * prefix, unsigned int vc, struct sk_buff * skb) {
#ifdef DEBUG_HORIZON
  unsigned int i;
  unsigned char * data = skb->data;
  PRINTDB (DBG_DATA, "%s(%u) ", prefix, vc);
  for (i=0; i<skb->len && i < 256;i++)
    PRINTDM (DBG_DATA, "%02x ", data[i]);
  PRINTDE (DBG_DATA,"");
#else
  (void) prefix;
  (void) vc;
  (void) skb;
#endif
  return;
}
