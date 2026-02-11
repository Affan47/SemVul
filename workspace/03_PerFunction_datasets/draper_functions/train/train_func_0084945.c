jshInit() {

#ifdef USE_WIRINGPI
  if (geteuid() == 0) {
    printf("RUNNING AS SUDO - awesome. You'll get proper IRQ support\n");
    wiringPiSetup();
  } else {
    printf("NOT RUNNING AS SUDO - sorry, you'll get rubbish realtime IO. You also need to export the pins you want to use first.\n");
    wiringPiSetupSys() ;
  }
#endif

  int i;
  for (i=0;i<=EV_DEVICE_MAX;i++)
    ioDevices[i] = 0;

  jshInitDevices();
#ifndef __MINGW32__
  if (!terminal_set) {
    struct termios new_termios;


    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));


    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
    terminal_set = 1;
  }
#endif
  for (i=0;i<JSH_PIN_COUNT;i++) {
    gpioState[i] = JSHPINSTATE_UNDEFINED;
    gpioEventFlags[i] = 0;
  }
#ifdef SYSFS_GPIO_DIR
  for (i=0;i<JSH_PIN_COUNT;i++) {
    gpioShouldWatch[i] = false;
  }
#endif

  isInitialised = true;
  int err = pthread_create(&inputThread, NULL, &jshInputThread, NULL);
  if (err != 0)
      printf("Unable to create input thread, %s", strerror(err));
}
