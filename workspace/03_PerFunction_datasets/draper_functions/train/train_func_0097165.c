openPipe(char *pipeName, char *mode) {
  FILE *pipe;
  fflush(stdout);
  if ((pipe = popen(pipeName, mode))) registerPipe(pipe);
  return pipe;
}
