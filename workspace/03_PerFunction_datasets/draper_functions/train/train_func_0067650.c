HttpRequestValidatorLevel(const HttpRequestData& request) {
  if (HV_GET != request.verb)
    return HVS_STRONG;
  return request.hasHeader(HH_RANGE, NULL) ? HVS_STRONG : HVS_WEAK;
}
