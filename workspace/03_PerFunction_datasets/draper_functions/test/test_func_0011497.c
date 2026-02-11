write_to_serial(int outfd, void *inbuf, int len)
{
  u_int8_t *p = inbuf;
  int i, ecode;
  struct ip *iphdr = inbuf;


  ecode = check_ip(inbuf, len);
  if(ecode < 0) {
    fprintf(stderr, "tun_to_serial: drop packet %d\n", ecode);
    return;
  }

  if(iphdr->ip_id == 0 && iphdr->ip_off & IP_DF) {
    uint16_t nid = htons(ip_id++);
    iphdr->ip_id = nid;
    nid = ~nid;
    iphdr->ip_sum += nid;
    if(iphdr->ip_sum < nid) {
      iphdr->ip_sum++;
    }
    ecode = check_ip(inbuf, len);
    if(ecode < 0) {
      fprintf(stderr, "tun_to_serial: drop packet %d\n", ecode);
      return;
    }
  }


  for(i = 0; i < len; i++) {
    switch(p[i]) {
    case SLIP_END:
      slip_send(outfd, SLIP_ESC);
      slip_send(outfd, SLIP_ESC_END);
      break;
    case SLIP_ESC:
      slip_send(outfd, SLIP_ESC);
      slip_send(outfd, SLIP_ESC_ESC);
      break;
    default:
      slip_send(outfd, p[i]);
      break;
    }

  }
  slip_send(outfd, SLIP_END);
  PROGRESS("t");
}
