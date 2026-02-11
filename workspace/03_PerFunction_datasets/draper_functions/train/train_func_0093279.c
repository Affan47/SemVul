start_and_destroy_clients(void* param)
#else
DWORD WINAPI start_and_destroy_clients(LPVOID param)
#endif
{
   const int total = 25;

   vector<UDTSOCKET> cli_socks;
   cli_socks.resize(total);

   if (createUDTSocket(cli_socks[0], 0) < 0)
   {
      cout << "socket: " << UDT::getlasterror().getErrorMessage() << endl;
      return NULL;
   }

   sockaddr* addr = NULL;
   int size = 0;

   addr = (sockaddr*)new sockaddr_in;
   size = sizeof(sockaddr_in);

   UDT::getsockname(cli_socks[0], addr, &size);
   char sharedport[NI_MAXSERV];
   getnameinfo(addr, size, NULL, 0, sharedport, sizeof(sharedport), NI_NUMERICSERV);

   for (int i = 1; i < total; ++ i)
   {
      if (createUDTSocket(cli_socks[i], atoi(sharedport)) < 0)
      {
         cout << "socket: " << UDT::getlasterror().getErrorMessage() << endl;
         return NULL;
      }
   }

   for (vector<UDTSOCKET>::iterator i = cli_socks.begin(); i != cli_socks.end(); ++ i)
   {
      if (connect(*i, g_Server_Port) < 0)
      {
         cout << "connect: " << UDT::getlasterror().getErrorMessage() << endl;
         return NULL;
      }
   }

   for (vector<UDTSOCKET>::iterator i = cli_socks.begin(); i != cli_socks.end(); ++ i)
   {
      UDT::close(*i);
   }

   return NULL;
}
