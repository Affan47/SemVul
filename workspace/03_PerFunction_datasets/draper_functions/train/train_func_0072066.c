jsvUnLockMany(unsigned int count, JsVar **vars) {
  while (count) jsvUnLock(vars[--count]);
}
