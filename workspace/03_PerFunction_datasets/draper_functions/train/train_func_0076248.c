Listen(int backlog) const {
  if (!IsValid()) {
    return false;
  }

  int status = listen(socket_, backlog);
  return status == 0;
}
