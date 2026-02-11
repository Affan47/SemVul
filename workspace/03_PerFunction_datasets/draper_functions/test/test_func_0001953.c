jswrap_io_digitalPulse(Pin pin, bool value, JsVar *times) {
  if (jsvIsNumeric(times)) {
    JsVarFloat time = jsvGetFloat(times);
    if (time<0 || isnan(time)) {
      jsExceptionHere(JSET_ERROR, "Pulse Time given for digitalPulse is less than 0, or not a number");
    } else {
      jshPinPulse(pin, value, time);
    }
  } else if (jsvIsIterable(times)) {

    JsvIterator it;
    jsvIteratorNew(&it, times);
    while (jsvIteratorHasElement(&it)) {
      JsVarFloat time = jsvIteratorGetFloatValue(&it);
      if (time>=0 && !isnan(time))
        jshPinPulse(pin, value, time);
      value = !value;
      jsvIteratorNext(&it);
    }
    jsvIteratorFree(&it);
  } else {
    jsExceptionHere(JSET_ERROR, "Expecting a number or array, got %t", times);
  }
}
