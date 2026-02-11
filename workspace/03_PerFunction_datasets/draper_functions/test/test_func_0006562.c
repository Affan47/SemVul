_nrrdCCAdj_2(unsigned char *out, unsigned int numid, const Nrrd *nin,
             unsigned int conny) {
  unsigned int (*lup)(const void *, size_t), x, y, sx, sy, id=0;
  double pid[5]={0,0,0,0,0};

  lup = nrrdUILookup[nin->type];
  sx = AIR_CAST(unsigned int, nin->axis[0].size);
  sy = AIR_CAST(unsigned int, nin->axis[1].size);
  for (y=0; y<sy; y++) {
    for (x=0; x<sx; x++) {
      if (!x) {
        pid[1] = GETV_2(-1, y);
        pid[2] = GETV_2(-1, y-1);
        pid[3] = GETV_2(0, y-1);
      } else {
        pid[1] = id;
        pid[2] = pid[3];
        pid[3] = pid[4];
      }
      pid[4] = GETV_2(x+1, y-1);
      id = AIR_CAST(unsigned int, GETV_2(x, y));
#define TADJ(P) \
      if (pid[(P)] != 0.5 && id != pid[(P)]) { \
        out[id + numid*AIR_CAST(unsigned int, pid[(P)])] = \
          out[AIR_CAST(unsigned int, pid[(P)]) + numid*id] = 1; \
      }
      TADJ(1);
      TADJ(3);
      if (2 == conny) {
        TADJ(2);
        TADJ(4);
      }
    }
  }

  return 0;
}
