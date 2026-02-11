sendCloseConnection(giopStrand* s)
{

  char hdr[12];
  hdr[0] = 'G'; hdr[1] = 'I'; hdr[2] = 'O'; hdr[3] = 'P';
  hdr[4] = s->version.major;   hdr[5] = s->version.minor;
  hdr[6] = _OMNIORB_HOST_BYTE_ORDER_;
  hdr[7] = (char)GIOP::CloseConnection;
  hdr[8] = hdr[9] = hdr[10] = hdr[11] = 0;

  if (omniORB::trace(25)) {
    omniORB::logger log;
    log << "sendCloseConnection: to " << s->connection->peeraddress()
	<< " 12 bytes\n";
  }
  if (omniORB::trace(30))
    giopStream::dumpbuf((unsigned char*)hdr, 12);

  s->connection->Send(hdr,12);
}
