eventTimer()
{
  if(send_state == SENDER_ACK){


    postEcho(send_seqnum, send_buf, send_bufsiz);

#ifdef LOGGING
    printf("rdttalk: time out. retransmit seq = %d\n", send_seqnum);
#endif
  }
}
