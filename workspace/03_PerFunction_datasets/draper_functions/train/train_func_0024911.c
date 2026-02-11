gagrel (struct gacmn *pcm) {
gaint i;

  for (i=0; i<pcm->relnum; i++) {
    if (pcm->type[i]==1) {
      gagfre (pcm->result[i].pgr);
    }
    else gasfre (pcm->result[i].stn);
  }
  pcm->numgrd = 0;
  pcm->relnum = 0;
}
