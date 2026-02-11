DoubleToBuffer(double value, char* buffer) {


  static_assert(DBL_DIG < 20, "DBL_DIG is too big.");

  if (value == inf()) {
    strcpy(buffer, "inf");
    return buffer;
  } else if (value == -inf()) {
    strcpy(buffer, "-inf");
    return buffer;
  } else if (IsNaN(value)) {
    strcpy(buffer, "nan");
    return buffer;
  }

  int snprintf_result =
    snprintf(buffer, kDoubleToBufferSize, "%.*g", DBL_DIG, value);


  KJ_DASSERT(snprintf_result > 0 && snprintf_result < kDoubleToBufferSize);


  volatile double parsed_value = strtod(buffer, NULL);
  if (parsed_value != value) {
    int snprintf_result =
      snprintf(buffer, kDoubleToBufferSize, "%.*g", DBL_DIG+2, value);


    KJ_DASSERT(snprintf_result > 0 && snprintf_result < kDoubleToBufferSize);
  }

  DelocalizeRadix(buffer);
  RemovePlus(buffer);
  return buffer;
}
