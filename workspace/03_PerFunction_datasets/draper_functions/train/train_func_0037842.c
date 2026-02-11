Tell_World_I_Have(size_t idx)
{
  PEERNODE *p;
  int f_seed = 0;

  if ( BTCONTENT.Seeding() ) f_seed = 1;

  for( p = m_head; p; p = p->next ){
    if( !PEER_IS_SUCCESS(p->peer) ) continue;


    if( (!p->peer->bitfield.IsFull() || 1==BTCONTENT.pBF->Count()) &&
        p->peer->stream.Send_Have(idx) < 0)
      p->peer->CloseConnection();

    else if( f_seed ){

      if( p->peer->SetLocal(M_NOT_INTERESTED) < 0 ){
        if(arg_verbose)
          CONSOLE.Debug("close: Can't set self not interested (T_W_I_H)");
        p->peer->CloseConnection();
      }
    }
  }
}
