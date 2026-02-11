onInput(Socket& socket)
{
    socket.removeSelector();
    log_debug("search socket " << static_cast<void*>(&socket) << " in idle sockets");
    _idleSockets.erase(&socket);

    if (socket.isConnected())
    {
        socket.inputConnection.close();
        socket.timeoutConnection.close();
        _eventLoop.commitEvent(ActiveSocketEvent(&socket));
    }
    else
    {
        log_debug("onInput; delete " << static_cast<void*>(&socket));
        delete &socket;
    }
}
