gageKindAnswerLength(const gageKind *kind, int item) {
  static const char me[]="gageKindAnswerLength";
  char *err;

  if (gageKindCheck(kind)) {
    err = biffGetDone(GAGE);
    fprintf(stderr, "%s: PANIC:\n %s", me, err);
    free(err); exit(1);
  }

  return (!airEnumValCheck(kind->enm, item)
          ? kind->table[item].answerLength
          : 0);
}
