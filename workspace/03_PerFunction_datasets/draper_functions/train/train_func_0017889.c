FetchFromOneSpansSafe(int N, void **start, void **end) {
  int result = FetchFromOneSpans(N, start, end);
  if (!result) {
    Populate();
    result = FetchFromOneSpans(N, start, end);
  }
  return result;
}
