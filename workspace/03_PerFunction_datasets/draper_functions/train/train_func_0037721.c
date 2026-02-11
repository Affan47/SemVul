findchannel()

{
  int j;

  j = 0;
  while ((j<MAXCHANS) && (channels[j] != 0)) {
    j = j + 1;
  };
  if (j >= MAXCHANS) {
    event_error("Too many channels required");
    j = 0;
  };
  channels[j] = 1;
  return (j);
}
