get_syslog_priority_from_log_level (GLogLevelFlags log_level)
{
        switch (log_level & G_LOG_LEVEL_MASK) {
        case G_LOG_FLAG_FATAL:
                return LOG_EMERG;
        case G_LOG_LEVEL_ERROR:

                return LOG_CRIT;
        case G_LOG_LEVEL_CRITICAL:

                return LOG_ERR;
        case G_LOG_LEVEL_WARNING:
        case G_LOG_LEVEL_MESSAGE:
                return LOG_NOTICE;
        case G_LOG_LEVEL_INFO:
                return LOG_INFO;
        case G_LOG_LEVEL_DEBUG:
        default:
                return LOG_DEBUG;
        }
}
