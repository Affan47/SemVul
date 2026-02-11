getLogLevelText(LogLevel level) {
    return LogLevelTexts[level>LOG_CRITICAL?LOG_CRITICAL+1:level];
}
