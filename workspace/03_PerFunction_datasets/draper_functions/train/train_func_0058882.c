ApiEntryCall(const char* name) {
#ifdef ENABLE_LOGGING_AND_PROFILING
  if (!Log::IsEnabled() || !FLAG_log_api) return;
  Logger::ApiEvent("api,%s\n", name);
#endif
}
