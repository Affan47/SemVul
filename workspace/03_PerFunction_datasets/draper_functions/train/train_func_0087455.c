my_net_set_write_timeout(NET *net, uint timeout)
{
  DBUG_ENTER("my_net_set_write_timeout");
  DBUG_PRINT("enter", ("timeout: %d", timeout));
  net->write_timeout= timeout;
#ifdef NO_ALARM
  if (net->vio)
    vio_timeout(net->vio, 1, timeout);
#endif
  DBUG_VOID_RETURN;
}
