AddServer(_Url &u)
{


   _Server *server = new _Server(u.host().get(), u.port());

   if(!server) return 0;

   servers.insert(std::make_pair(u.signature(), server));

   server->SetID(_Server::IncrementTotServers());

   return server;

}
