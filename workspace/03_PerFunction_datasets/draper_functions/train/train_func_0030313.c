GPS_Packet_New(void)
{
  GPS_PPacket ret;
  int hdr_size = sizeof(GPS_OPacket) ;
  if (!(ret=(GPS_PPacket)calloc(1, hdr_size)))

  {
    perror("malloc");
    fprintf(stderr,"GPS_Packet_New: Insufficient memory");
    fflush(stderr);
    return NULL;
  }
  if (!(ret->data = (UC*)calloc(1, MAX_GPS_PACKET_SIZE*sizeof(UC)))) {
    perror("malloc");
    fprintf(stderr,"GPS_Packet_New: Insufficient data memory");
    fflush(stderr);
    return NULL;
  }

  return ret;
}
