StopDownload()
{
  PEERNODE *p = m_head;

  for( ; p; p = p->next ){
    if( p->peer->SetLocal(M_NOT_INTERESTED) < 0 ){
      p->peer->CloseConnection();
    }else p->peer->PutPending();
  }
}
