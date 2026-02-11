onInput(StreamBuffer& sb)
{
    log_debug("onInput");

    sb.endRead();

    if (sb.in_avail() == 0 || sb.device()->eof())
    {
        close();
        return;
    }

    while (sb.in_avail() > 0)
    {
        if (_responder.advance(sb.sbumpc()))
        {
            _responder.finalize(_stream);
            buffer().beginWrite();
            onOutput(sb);
            return;
        }
    }

    sb.beginRead();

}
