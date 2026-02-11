OpenConnection()
{
   if (!_connection) return 0;

   if(_connection->IsOpen() && _connection->IsConnected())
      return -1;


   if(_connection->Open() == NOTOK) return 0;

   _tot_open ++;
   return 1;
}
