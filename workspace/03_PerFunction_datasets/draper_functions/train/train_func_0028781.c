erase ( iterator i )
{
  Connection * con = i->second;

  KernelDeviceToConnection::instance().erase( i->first );
  _connections.erase ( i );
  delete con;
}
