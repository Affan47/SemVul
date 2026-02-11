jswrap_spi_setup(JsVar *parent, JsVar *options) {
  IOEventFlags device = jsiGetDeviceFromClass(parent);
  JshSPIInfo inf;
  jsspiPopulateSPIInfo(&inf, options);

  if (DEVICE_IS_SPI(device)) {
    jshSPISetup(device, &inf);
#ifdef LINUX
    if (jsvIsObject(options)) {
      jsvUnLock(jsvObjectSetChild(parent, "path", jsvObjectGetChild(options, "path", 0)));
    }
#endif
  } else if (device == EV_NONE) {

    if (inf.pinSCK != PIN_UNDEFINED)
      jshPinSetState(inf.pinSCK,  JSHPINSTATE_GPIO_OUT);
    if (inf.pinMISO != PIN_UNDEFINED)
      jshPinSetState(inf.pinMISO,  JSHPINSTATE_GPIO_IN);
    if (inf.pinMOSI != PIN_UNDEFINED)
      jshPinSetState(inf.pinMOSI,  JSHPINSTATE_GPIO_OUT);
  } else return;

  if (options)
    jsvUnLock(jsvSetNamedChild(parent, options, DEVICE_OPTIONS_NAME));
  else
    jsvRemoveNamedChild(parent, DEVICE_OPTIONS_NAME);
}
