Preparse(UnicodeInputStream* input, size_t max_stack) {
  internal::InputStreamUTF16Buffer buffer(input);
  uintptr_t stack_limit = reinterpret_cast<uintptr_t>(&buffer) - max_stack;
  internal::UnicodeCache unicode_cache;
  internal::JavaScriptScanner scanner(&unicode_cache);
  scanner.Initialize(&buffer);
  internal::CompleteParserRecorder recorder;
  preparser::PreParser::PreParseResult result =
      preparser::PreParser::PreParseProgram(&scanner,
                                            &recorder,
                                            true,
                                            stack_limit);
  if (result == preparser::PreParser::kPreParseStackOverflow) {
    return PreParserData::StackOverflow();
  }
  internal::Vector<unsigned> pre_data = recorder.ExtractData();
  size_t size = pre_data.length() * sizeof(pre_data[0]);
  unsigned char* data = reinterpret_cast<unsigned char*>(pre_data.start());
  return PreParserData(size, data);
}
