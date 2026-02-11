GetConnectLevel() const
{
   if(!conn)
      return CL_NOT_CONNECTED;
   if(state==CONNECTING_STATE || state==HTTP_PROXY_CONNECTED)
      return CL_CONNECTING;
   if(state==CONNECTED_STATE)
      return CL_JUST_CONNECTED;
   if(state==USER_RESP_WAITING_STATE)
      return CL_NOT_LOGGED_IN;
   if(conn->quit_sent)
      return CL_JUST_BEFORE_DISCONNECT;
   return CL_LOGGED_IN;
}
