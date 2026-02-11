readln (QString &line, bool autoAck, bool *partial)
{
  int len;

  if ( autoAck ) {
     d->readsignalon=true;
  }


  len = d->recvbuffer.indexOf('\n', d->rbi) - d->rbi;


  if ( ( len < 0 ) &&
       ( d->rbi < d->recvbuffer.length() ) ) {
     d->recvbuffer = d->recvbuffer.mid( d->rbi );
     d->rbi = 0;
     if (partial)
     {
        len = d->recvbuffer.length();
        line = d->recvbuffer;
        d->recvbuffer = "";
        *partial = true;
        return len;
     }
     return -1;
  }

  if (len>=0)
  {
     line = d->codec->toUnicode( d->recvbuffer.mid( d->rbi, len ) );
     d->rbi += len + 1;
     if (partial)
        *partial = false;
     return len;
  }

  d->recvbuffer = "";
  d->rbi = 0;


  return -1;

}
