getNewEVEXTI() {
  int i;
  for (i=0;i<16;i++) {
    IOEventFlags evFlag = (IOEventFlags)(EV_EXTI0+i);
    Pin pin;
    bool found = false;
    for (pin=0;pin<JSH_PIN_COUNT;pin++)
      if (gpioEventFlags[pin] == evFlag)
        found = true;
    if (!found)
      return evFlag;
  }
  return 0;
}
