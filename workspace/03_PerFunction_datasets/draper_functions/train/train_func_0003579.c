rx_enum_ordered(int len, int avail, char *prefix,
		    const struct regex_t *rx, time_t *t0) {
  if(CtrlC || (PasswordLeft == 0)) return;

  if(rx) {
    int j;

    if(rx->wild) {
      if(avail) {
        for(j = 0; j < BYTE_MAX; j ++) {
          if(rx->symbol[j] > 0) {
            prefix[len] = j;
            rx_enum_ordered(len + 1, avail - 1, prefix, rx, t0);
          }
        }
      }

      rx_enum_ordered(len, avail, prefix, rx->next, t0);
    } else {
      for(j = 0; j < BYTE_MAX; j ++) {
	if(rx->symbol[j] > 0) {
	  prefix[len] = j;
	  rx_enum_ordered(len + 1, avail, prefix, rx->next, t0);
	}
      }
    }
  } else if(len && (avail == 0)) {
    time_t t1;

    if(verbose && ((t1 = time(NULL)) > *t0)) {
      fprintf(stderr, "KEY: ");
      print_key(stderr, prefix, len);
      fprintf(stderr, "\r");
      fflush(stderr);
      *t0 = t1;
    }

    KEY_cmp(prefix, len);
  }
}
