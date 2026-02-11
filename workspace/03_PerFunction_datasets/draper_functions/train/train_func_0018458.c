jswrap_io_digitalRead(JsVar *pinVar) {
  if (jsvIsArray(pinVar)) {
    int pins = 0;
    JsVarInt value = 0;
    JsvObjectIterator it;
    jsvObjectIteratorNew(&it, pinVar);
    while (jsvObjectIteratorHasValue(&it)) {
      JsVar *pinPtr = jsvObjectIteratorGetValue(&it);
      value = (value<<1) | (JsVarInt)jshPinInput(jshGetPinFromVar(pinPtr));
      jsvUnLock(pinPtr);
      jsvObjectIteratorNext(&it);
      pins++;
    }
    jsvObjectIteratorFree(&it);
    if (pins==0) return 0;
    return value;
  } else {
    Pin pin = jshGetPinFromVar(pinVar);
    return jshPinInput(pin);
  }
}
