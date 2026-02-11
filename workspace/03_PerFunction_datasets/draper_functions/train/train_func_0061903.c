SendConnectRequest()
{
   LogNote(9,"connecting...");
   Buffer req;
   req.PackUINT64BE(connect_magic);
   req.PackUINT32BE(a_connect);
   req.PackUINT32BE(NewTransactionId());
   if(!SendPacket(req))
      return false;
   current_action=a_connect;
   return true;
}
