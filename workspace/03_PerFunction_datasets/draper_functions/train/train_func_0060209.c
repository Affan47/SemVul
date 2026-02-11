findGSeqTrack(int gsid) {
  GSeqTrack f(gsid);
  int fidx=-1;
  if (gseqtracks.Found(&f,fidx))
     return gseqtracks[fidx];
  fidx=gseqtracks.Add(new GSeqTrack(gsid));
  return gseqtracks[fidx];
}
