jswrap_waveform_stop(JsVar *waveform) {
  bool running = jsvGetBoolAndUnLock(jsvObjectGetChild(waveform, "running", 0));
  if (!running) {
    jsExceptionHere(JSET_ERROR, "Waveform is not running");
    return;
  }
  JsVar *buffer = jswrap_waveform_getBuffer(waveform,0,0);
  if (!jstStopBufferTimerTask(buffer)) {
    jsExceptionHere(JSET_ERROR, "Waveform couldn't be stopped");
  }
  jsvUnLock(buffer);

  jswrap_waveform_idle();
}
