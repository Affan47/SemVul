biffMsgAdd(biffMsg *msg, const char *err) {
  static const char me[]="biffMsgAdd";
  unsigned int idx;

  if (biffMsgNoop == msg) {
    return;
  }
  if (!( msg && err )) {
    fprintf(stderr, "%s: PANIC got NULL msg (%p) or err (%p)\n", me,
            AIR_VOIDP(msg), AIR_CVOIDP(err));
    return;
  }
  idx = airArrayLenIncr(msg->errArr, 1);
  if (!msg->err) {
    fprintf(stderr, "%s: PANIC: couldn't add message to %s\n", me, msg->key);
    return;
  }
  if (!( msg->err[idx] = airOneLinify(airStrdup(err)) )) {
    fprintf(stderr, "%s: PANIC: couldn't alloc message to %s\n", me, msg->key);
    return;
  }
  return;
}
