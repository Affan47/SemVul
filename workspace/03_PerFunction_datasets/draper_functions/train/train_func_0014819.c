CloseAllConnectionToSeed()
{
  PEERNODE *p = m_head;
  for( ; p; p = p->next ){
    if( p->peer->bitfield.IsFull() ||


        (PEER_IS_SUCCESS(p->peer) && !p->peer->Is_Remote_Interested() &&
          BTCONTENT.GetSeedTime() - now >= 300 &&
          !p->peer->ConnectedWhileSeed()) ){
      p->peer->DontWantAgain();
      if(arg_verbose) CONSOLE.Debug("close: seed<->seed");
      p->peer->CloseConnection();
    }
    else p->peer->stream.in_buffer.SetSize(BUF_DEF_SIZ);
  }
}
