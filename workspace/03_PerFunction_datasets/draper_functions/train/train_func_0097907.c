txt_trackend()
{

  if (playinghead != NULL) {
    printf("Error in MIDI file - notes still on at end of track!\n");
  };
  track[trackno].tracklen = Mf_currtime - track[trackno].tracklen;
  trackno = trackno + 1;
  trackcount = trackcount + 1;
}
