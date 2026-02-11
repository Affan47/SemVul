EstablishConnection()
{

   int result;


   result=OpenConnection();

   if (!result)
   	 return Connection_open_failed;
   else  if(debug > 4)
         {
            cout << setw(5) << Transport::GetTotOpen() << " - ";

   	    if (result == -1)
	       cout << "Connection already open. No need to re-open." << endl;
	    else
	       cout << "Open of the connection ok" << endl;
         }


   if(result==1)
   {


      if ( !AssignConnectionServer() )
      	 return Connection_no_server;
	 else if (debug > 4)
	       cout << "\tAssigned the remote host " << _url.host() << endl;


      if ( !AssignConnectionPort() )
      	 return Connection_no_port;
	 else if (debug > 4)
	       cout << "\tAssigned the port " << _url.port() << endl;
   }


   if (! (result = Connect()))
   	 return Connection_failed;
   else if (result == -1) return Connection_already_up;
	    else return Connection_ok;

}
