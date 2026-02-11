FloatToBuffer(float value, char* buffer) {


  static_assert(FLT_DIG < 10, "FLT_DIG is too big");

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
    snprintf(buffer, kFloatToBufferSize, "%.*g", FLT_DIG, value);


  KJ_DASSERT(snprintf_result > 0 && snprintf_result < kFloatToBufferSize);

  float parsed_value;
  if (!safe_strtof(buffer, &parsed_value) || parsed_value != value) {
    int snprintf_result =
      snprintf(buffer, kFloatToBufferSize, "%.*g", FLT_DIG+2, value);


    KJ_DASSERT(snprintf_result > 0 && snprintf_result < kFloatToBufferSize);
  }

  DelocalizeRadix(buffer);
  RemovePlus(buffer);
  return buffer;
}
