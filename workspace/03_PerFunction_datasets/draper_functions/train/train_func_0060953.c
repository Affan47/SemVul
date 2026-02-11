convertToBuffer(const spi::InternalLoggingEvent& event,
    const tstring& serverName)
{
    SocketBuffer buffer(LOG4CPLUS_MAX_MESSAGE_SIZE - sizeof(unsigned int));

    buffer.appendByte(LOG4CPLUS_MESSAGE_VERSION);
    buffer.appendByte(1);

    buffer.appendString(serverName);
    buffer.appendString(event.getLoggerName());
    buffer.appendInt(event.getLogLevel());
    buffer.appendString(event.getNDC());
    buffer.appendString(event.getMessage());
    buffer.appendString(event.getThread());
    buffer.appendInt( OFstatic_cast(unsigned int, event.getTimestamp().sec()) );
    buffer.appendInt( OFstatic_cast(unsigned int, event.getTimestamp().usec()) );
    buffer.appendString(event.getFile());
    buffer.appendInt(event.getLine());

    return buffer;
}
