APieceComplete(size_t idx)
{
  unsigned char md[20];
  if(pBF->IsSet(idx)) return 1;
  if( GetHashValue(idx, md) < 0 ){

    Uncache(idx);
    return -1;
  }

  if( memcmp(md,(m_hash_table + idx * 20), 20) != 0 ){
    CONSOLE.Warning(3, "warn, piece %d hash check failed.", idx);
    Uncache(idx);
    CountHashFailure();
    return 0;
  }

  pBF->Set(idx);
  m_left_bytes -= GetPieceLength(idx);
  Tracker.CountDL(GetPieceLength(idx));


  if( cfg_cache_size ){
    if( IsFull() ){
      FlushCache();
      for( size_t n=1; n <= m_btfiles.GetNFiles(); n++ )
        m_btfiles.CloseFile(n);
    }
    if( !IsFull() || m_flush_failed ){
      BTFLUSH *last = m_flushq;
      BTFLUSH *node = new BTFLUSH;
      if( !node ) FlushPiece(idx);
      else{
        node->idx = idx;
        node->next = (BTFLUSH *)0;
        if( last ){
          for( ; last->next; last = last->next);
          last->next = node;
        }else m_flushq = node;
      }
    }
  }

  return 1;
}
