ScanPeers() {

   for(int i=0; i<peers.count(); i++) {
      const TorrentPeer *peer=peers[i];
      if(peer->Failed())
	 LogError(2,"peer %s failed: %s",peer->GetName(),peer->ErrorText());
      else if(peer->Disconnected())
	 LogNote(4,"peer %s disconnected",peer->GetName());
      else if(peer->myself) {
	 LogNote(4,"removing myself-connected peer %s",peer->GetName());
	 BlackListPeer(peer,"forever");
      } else if(peer->duplicate) {
	 LogNote(4,"removing duplicate peer %s",peer->GetName());
      } else if(complete && peer->Seed())
	 LogNote(4,"removing unneeded peer %s (%s)",peer->GetName(),peers[i]->Status());
      else
	 continue;
      peers.remove(i--);
   }
   ReducePeers();
   peers_scan_timer.Reset();
}
