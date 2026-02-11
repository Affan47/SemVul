InitMP3(void)
{
  if(mdebug==7)printf("\nInitMP3");


  if (gmp==NULL) {
     gmp=(struct mpstr *)malloc(sizeof(struct mpstr)*8);
  if(mdebug==7)printf("\nafter gmp=(struct...");
  }
  memset(gmp, 0, sizeof(struct mpstr)*8);

  if(mdebug==7)printf("\nafter memset(gmp, 0,...");


  gmp->framesize = 0;
  gmp->fsizeold = -1;
  gmp->bsize = 0;
  gmp->head = gmp->tail = NULL;
  gmp->fr.single = -1;
  gmp->bsnum = 0;
  gmp->synth_bo = 1;

  if(mdebug==7)printf("\nbefore init_layer3\n");
  init_layer3(SBLIMIT);
  if(mdebug==7)printf("\nafter init_layer3\n");

  return !0;
}
