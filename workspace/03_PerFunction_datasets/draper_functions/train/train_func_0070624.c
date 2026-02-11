AddPeer(TorrentPeer *peer)
{
   if(black_list->Listed(peer->GetAddress())) {
      delete peer;
      return;
   }
   for(int i=0; i<peers.count(); i++) {
      if(peers[i]->AddressEq(peer)) {
	 if(peer->Connected() && !peers[i]->Connected()) {
	    peers[i]=peer;
	 } else {
	    delete peer;
	 }
	 return;
      }
   }
   peers.append(peer);
}
