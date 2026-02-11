SimpleItoa(unsigned long long i) {
  char buffer[kFastToBufferSize];
  return string(buffer, (sizeof(i) == 4) ?
    FastUInt32ToBufferLeft(i, buffer) :
    FastUInt64ToBufferLeft(i, buffer));
}
