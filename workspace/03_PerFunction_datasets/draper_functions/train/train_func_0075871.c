inf_io_update_watch(InfIo* io,
                    InfIoWatch* watch,
                    InfIoEvent events)
{
  InfIoIface* iface;

  g_return_if_fail(INF_IS_IO(io));
  g_return_if_fail(watch != NULL);

  iface = INF_IO_GET_IFACE(io);
  g_return_if_fail(iface->update_watch != NULL);

  iface->update_watch(io, watch, events);
}
