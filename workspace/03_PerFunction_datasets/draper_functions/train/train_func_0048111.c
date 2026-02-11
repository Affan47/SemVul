biffDone(const char *key) {
  static const char me[]="biffDone";
  unsigned int idx;
  biffMsg *msg;

  _bmsgStart();

  msg = _bmsgFind(key);
  if (!msg) {
    fprintf(stderr, "%s: WARNING: no information for key \"%s\"\n", me, key);
    return;
  }
  idx = _bmsgFindIdx(msg);
  biffMsgNix(msg);
  if (_bmsgNum > 1) {


    _bmsg[idx] = _bmsg[_bmsgNum-1];
  }
  airArrayLenIncr(_bmsgArr, -1);

  if (!_bmsgArr->len) {
    _bmsgFinish();
  }

  return;
}
