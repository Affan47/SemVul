registerPipe(FILE *p) {
  if (numPipes >= MAX_PIPES) svd_error("Too many pipes open");
  Pipe[numPipes++] = p;
}
