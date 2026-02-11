readsig(a, b, sig)
int *a, *b;
char **sig;

{
  int t;

  if ((**sig == 'C') || (**sig == 'c')) {
    *a = 4;
    *b = 4;
    return;
  };
  *a = readnump(sig);
  if ((int)**sig != '/') {
    event_error("Missing / ");
  } else {
    *sig = *sig + 1;
  };
  *b = readnump(sig);
  if ((*a == 0) || (*b == 0)) {
    event_error("Expecting fraction in form A/B");
  } else {
    t = *b;
    while (t > 1) {
      if (t%2 != 0) {
        event_error("divisor must be a power of 2");
        t = 1;
        *b = 0;
      } else {
        t = t/2;
      };
    };
  };
}
