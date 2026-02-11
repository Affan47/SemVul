jswrap_onewire_write(JsVar *parent, JsVar *data, bool leavePowerOn) {
  Pin pin = onewire_getpin(parent);
  if (!jshIsPinValid(pin)) return;

  jsvIterateCallback(data, (void (*)(int,  void *))_jswrap_onewire_write_cb, (void*)&pin);

  if (!leavePowerOn) {
    jshPinSetState(pin, JSHPINSTATE_GPIO_IN);
    jshPinSetValue(pin, 0);
  }
}
