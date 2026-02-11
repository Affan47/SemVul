fillvoice(partno, xtrack, voice)


int partno, xtrack, voice;
{
  char msg[100];
  long now;

  now = tracklen + delta_time;
  if (partlabel == -1) {
    if (xtrack == 1) {
      introlen = now;
    } else {
      if (now == 0) {
        delta_time = delta_time + introlen;
        now = introlen;
      } else {
        if (now != introlen) {
          sprintf(msg, "Time 0-%ld voice %d, has length %ld",
                  introlen, voice, now);
          event_error(msg);
        };
      };
    };
  } else {
    if (xtrack == 1) {
      partlen[partlabel] = now - lastlen;
    } else {
      if (now - lastlen == 0) {
        delta_time = delta_time + partlen[partlabel];
        now = now + partlen[partlabel];
      } else {
        if (now - lastlen != partlen[partlabel]) {
          sprintf(msg, "Time %ld-%ld voice %d, part %c has length %ld",
                  lastlen, lastlen+partlen[partlabel], voice,
                  (char) (partlabel + (int) 'A'),
                  now-lastlen);
          event_error(msg);
        };
      };
    };
  };
  lastlen = now;
}
