extractConfiguration(const InstrumentHeader* header, const float* go, int16_t* ci, float* c, float* o) const
  {

    for (int i = 0 ; i < 6 ; ++i)
      ci[i] = header->channels[i]+1;


    const float cx = header->width / 2.0f;
    const float cy = header->length / 2.0f;
    c[0] =    cx + go[0];
    c[1] =   -cy + go[1];
    c[2] =  0.0f + go[2];
    c[3] =   -cx + go[0];
    c[4] =   -cy + go[1];
    c[5] =  0.0f + go[2];
    c[6] =   -cx + go[0];
    c[7] =    cy + go[1];
    c[8] =  0.0f + go[2];
    c[9] =    cx + go[0];
    c[10] =   cy + go[1];
    c[11] = 0.0f + go[2];

    o[0] = header->offset[0];
    o[1] = header->offset[1];
    o[2] = header->offset[2];
  }
