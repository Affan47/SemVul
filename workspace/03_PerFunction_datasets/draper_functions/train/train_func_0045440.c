SendHandshake()
{
   const char *const protocol="BitTorrent protocol";
   int proto_len=strlen(protocol);
   send_buf->PackUINT8(proto_len);
   send_buf->Put(protocol,proto_len);
   static char extensions[8] = {


      0, 0, 0, 0, 0, 0x10, 0, 0x05,
   };
   if(ResMgr::QueryBool("torrent:use-dht",0))
      extensions[7]|=0x01;
   else
      extensions[7]&=~0x01;
   send_buf->Put(extensions,8);
   send_buf->Put(parent->info_hash);
   send_buf->Put(parent->my_peer_id);
   LogSend(9,"handshake");
}
