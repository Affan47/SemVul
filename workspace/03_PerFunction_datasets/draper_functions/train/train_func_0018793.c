TestLogSink() {
  TestLogSinkImpl sink;
  LogSink *no_sink = NULL;

  LOG_TO_SINK(&sink, INFO) << "LOG_TO_SINK: " << "collected info";
  LOG_TO_SINK(&sink, WARNING) << "LOG_TO_SINK: " << "collected warning";
  LOG_TO_SINK(&sink, ERROR) << "LOG_TO_SINK: " << "collected error";

  LOG_TO_SINK(no_sink, INFO) << "LOG_TO_SINK: " << "reported info";
  LOG_TO_SINK(no_sink, WARNING) << "LOG_TO_SINK: " << "reported warning";
  LOG_TO_SINK(NULL, ERROR) << "LOG_TO_SINK: " << "reported error";

  LOG_TO_SINK_BUT_NOT_TO_LOGFILE(&sink, INFO)
      << "LOG_TO_SINK_BUT_NOT_TO_LOGFILE: " << "collected info";
  LOG_TO_SINK_BUT_NOT_TO_LOGFILE(&sink, WARNING)
      << "LOG_TO_SINK_BUT_NOT_TO_LOGFILE: " << "collected warning";
  LOG_TO_SINK_BUT_NOT_TO_LOGFILE(&sink, ERROR)
      << "LOG_TO_SINK_BUT_NOT_TO_LOGFILE: " << "collected error";

  LOG_TO_SINK_BUT_NOT_TO_LOGFILE(no_sink, INFO)
      << "LOG_TO_SINK_BUT_NOT_TO_LOGFILE: " << "thrashed info";
  LOG_TO_SINK_BUT_NOT_TO_LOGFILE(no_sink, WARNING)
      << "LOG_TO_SINK_BUT_NOT_TO_LOGFILE: " << "thrashed warning";
  LOG_TO_SINK_BUT_NOT_TO_LOGFILE(NULL, ERROR)
      << "LOG_TO_SINK_BUT_NOT_TO_LOGFILE: " << "thrashed error";

  LOG(INFO) << "Captured by LOG_TO_SINK:";
  for (size_t i = 0; i < sink.errors.size(); ++i) {
    LogMessage("foo", LogMessage::kNoLogPrefix, INFO).stream()
      << sink.errors[i];
  }
}
