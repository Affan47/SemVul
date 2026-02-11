Attach(AsyncSocket* socket) {
  if (socket_)
    delete socket_;
  socket_ = socket;
  if (socket_) {
    socket_->SignalConnectEvent.connect(this, &SocketStream::OnConnectEvent);
    socket_->SignalReadEvent.connect(this,    &SocketStream::OnReadEvent);
    socket_->SignalWriteEvent.connect(this,   &SocketStream::OnWriteEvent);
    socket_->SignalCloseEvent.connect(this,   &SocketStream::OnCloseEvent);
  }
}
