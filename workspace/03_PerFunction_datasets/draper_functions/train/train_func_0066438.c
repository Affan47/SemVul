set_transp_proto(int x, ErrorHandler *errh)
{
  if (_transp_proto != UNKNOWN && _transp_proto != x)
    errh->error("transport protocol specified twice");
  _transp_proto = x;
}
