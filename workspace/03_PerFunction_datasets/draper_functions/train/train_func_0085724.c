ConnectorThread (
    SocketAppender & socket_appender)
    : sa (socket_appender)
    , trigger_ev ()
    , exit_flag (false)
{ }
