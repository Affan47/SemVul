caml_extunix_crtscts(value mlfd)
{
  CAMLparam1(mlfd);
  struct termios t;
  int r, fd = Int_val(mlfd);

  r = tcgetattr(fd, &t);
  if (0 == r) {
    t.c_cflag |= CRTSCTS;
    r = tcsetattr(fd, TCSANOW, &t);
  }
  if (0 != r) uerror("crtscts",Nothing);
  CAMLreturn(Val_unit);
}
