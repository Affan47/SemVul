redirect_output(bool redirect, int fileno, int *pipedes)
{
  if(redirect) {
    close(fileno);
    dup2(pipedes[1], fileno);
    close(pipedes[1]);
    fcntl(fileno, F_SETFL, O_NONBLOCK);
  }
  else {
    close(pipedes[1]);
    close(fileno);
  }
  close(pipedes[0]);
}
