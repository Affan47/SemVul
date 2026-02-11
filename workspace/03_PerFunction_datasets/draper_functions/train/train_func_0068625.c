isActive_req( const Command* action )
{
   if ( commandState_request.find( action ) != commandState_request.end() )
      return commandState_request[action];
   else {
      commandState_request = commandState_map;
      if ( commandState_request.find( action ) != commandState_request.end() )
         return commandState_request[action];
      else
         return false;
   }
}
