_gageOffValueUpdate(gageContext *ctx) {
  static const char me[]="_gageOffValueUpdate";
  int fd, i, j, k;
  unsigned int sx, sy;

  if (ctx->verbose) fprintf(stderr, "%s: hello\n", me);

  sx = ctx->shape->size[0];
  sy = ctx->shape->size[1];
  fd = 2*ctx->radius;

  for (k=0; k<fd; k++) {
    for (j=0; j<fd; j++) {
      for (i=0; i<fd; i++) {
        ctx->off[i + fd*(j + fd*k)] = i + sx*(j + sy*k);
      }
    }
  }

  if (ctx->verbose) fprintf(stderr, "%s: bye\n", me);

  return;
}
