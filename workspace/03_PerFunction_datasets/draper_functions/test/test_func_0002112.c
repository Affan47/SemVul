onConnect(net::TcpSocket& socket)
{
    try
    {
        log_trace("onConnect");

        _exceptionPending = false;
        socket.endConnect();

        _stream.buffer().beginWrite();
    }
    catch (const std::exception& )
    {
        IRemoteProcedure* proc = _proc;
        cancel();

        if (!proc)
            throw;

        _exceptionPending = true;
        proc->onFinished();

        if (_exceptionPending)
            throw;
    }
}
