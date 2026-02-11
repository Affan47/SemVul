CleanPeers()
{
   Enter();

   for(int i=0; i<peers.count(); i++) {
      const TorrentPeer *peer=peers[i];
      if(peer->ActivityTimedOut()) {
	 LogNote(4,"removing uninteresting peer %s (%s)",peer->GetName(),peers[i]->Status());
	 BlackListPeer(peer,"2h");
	 peers.remove(i--);
      }
   }
   Leave();
}
