subst(const char* format, int args, const Subst arg[]) {

  string result;
  const char* i = format - 1;
  char max = '1' + args;
  while (*++i != '\0') {
    if (*i != '%') { result += *i; continue; }
    ++i;
    const char* iPos = i;
    while (*i == 'F' || *i == 'L' || *i == 'E') ++i;
    if (*i == '\0') break;
    if (*i == '%') { result += '%'; continue; }

    if (*i >= '1' && *i < max) {
      int n = *i - '1';
      switch (arg[n].type) {
        case INT:
          snprintf(buf, BUF_LEN, "%d", arg[n].val.intVal);
          buf[BUF_LEN - 1] = '\0'; result += buf; break;
        case UNSIGNED:
          snprintf(buf, BUF_LEN, "%u", arg[n].val.unsignedVal);
          buf[BUF_LEN - 1] = '\0'; result += buf; break;
        case LONG:
          snprintf(buf, BUF_LEN, "%ld", arg[n].val.longVal);
          buf[BUF_LEN - 1] = '\0'; result += buf; break;
        case ULONG:
          snprintf(buf, BUF_LEN, "%lu", arg[n].val.ulongVal);
          buf[BUF_LEN - 1] = '\0'; result += buf; break;
#       if HAVE_UNSIGNED_LONG_LONG
        case ULONGLONG:
          snprintf(buf, BUF_LEN, "%llu", arg[n].val.ulonglongVal);
          buf[BUF_LEN - 1] = '\0'; result += buf; break;
#       endif
        case DOUBLE:
          snprintf(buf, BUF_LEN, "%f", arg[n].val.doubleVal);
          buf[BUF_LEN - 1] = '\0'; result += buf; break;
        case CHAR:
          result += arg[n].val.charVal; break;
        case CHAR_P:
          result += arg[n].val.charPtr; break;
        case STRING_P:
          result += *arg[n].val.stringPtr; break;
        case POINTER:
          snprintf(buf, BUF_LEN, "%p", arg[n].val.pointerVal);
          buf[BUF_LEN - 1] = '\0'; result += buf; break;
      }
      continue;
    }
    i = iPos;
    result += '%';
    result += *i;
  }

  return result;
}
