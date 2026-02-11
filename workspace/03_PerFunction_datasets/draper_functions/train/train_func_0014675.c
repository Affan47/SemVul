set_param_val(char *cntrl, int lcval, int rcval) {
  int len, i, d;

#ifdef DEBUG
  fprintf(stderr, "set_param_val(%s, %d, %d)\n", cntrl, lcval, rcval);
#endif

  if (!init_flag) {
    if (open_mixer()) {
      return(-1);
    }
  }
  len = strlen(cntrl);
  for (i = 0; i < SOUND_MIXER_NRDEVICES; i++) {
    if (0 == strncmp(dname[i], cntrl, len)) {
      d = (1 << i);
      if (0 != (devmask & d)) {
	lcval = (lcval < 0 ? 0 : (lcval > 100 ? 100 : lcval));
	if (d & stereod) {
	  rcval = (rcval < 0 ? 0 : (rcval > 100 ? 100 : rcval));
	  lcval |= (rcval << 8);
	}
	if (-1 == ioctl(mixer_fd, MIXER_WRITE(i), &lcval)) {
	  perror("MIXER_WRITE");
	  if (!init_flag)
	    close_mixer();
	  return(-1);
	}
      }
      break;
    }
  }
  if (!init_flag)
    close_mixer();
  return(0);
}
