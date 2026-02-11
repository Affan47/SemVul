caml_rev_convert_signal_number(int signo)
{
  int i;
  for (i = 0; i < sizeof(posix_signals) / sizeof(int); i++)
    if (signo == posix_signals[i]) return -i - 1;
  return signo;
}
