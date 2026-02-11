datalink_pcap(u_char * user, const struct pcap_pkthdr * h, u_char * pkt)
{
  int            linktype = -1;
  u_int32_t *    link;
  struct timeval tv;


  link = (u_int32_t *) user;
  switch(*link)
    {
    case DLT_NULL:
      linktype = DATALINK_TYPE_NULL;
      break;

    case DLT_EN10MB:
      linktype = DATALINK_TYPE_ETHERNET;
      break;

    case DLT_SLIP:
      linktype = DATALINK_TYPE_SLIP;
      break;

    case DLT_PPP:
      linktype = DATALINK_TYPE_PPP;
      break;

#ifdef DLT_RAW
    case DLT_RAW:
      linktype = DATALINK_TYPE_RAWIP;
      break;
#endif
    default:
      error_fatal("\ncannot handle data link type %d", link);
    }


  tv.tv_sec = h->ts.tv_sec;
  tv.tv_usec = h->ts.tv_usec;


  datalink(linktype, tv, h->caplen, h->len, pkt);
}
