InitFluid()
{
  gu = (ValueArray*) malloc(sizeof(ValueArray));
  gv = (ValueArray*) malloc(sizeof(ValueArray));
  gu_old = (ValueArray*) malloc(sizeof(ValueArray));
  gv_old = (ValueArray*) malloc(sizeof(ValueArray));
  particles = (ParticleArray*) malloc(sizeof(ParticleArray));

  int i,j,l;
  l = 0;
  for (i = 0; i < SIZE; ++i) {
    for (j = 0; j < SIZE; ++j) {
      (*gu)[i][j] = 0;
      (*gv)[i][j] = 0;
      (*gu_old)[i][j] = 0;
      (*gv_old)[i][j] = 0;
    }
  }

  for (i = 0 ; i < NUM_PARTICLES ; i++) {
    (*particles)[i].x = random_float(1,SIZE-1);
    (*particles)[i].y = random_float(1,SIZE-1);
  }
}
