readOne(void)
{
  ipcWarn(wrnlvl(),"%t pString_Connection::readOne\n");
  MSBuffer *hb=headBuffer();
  MSBuffer *db=readBuffer();
  int slen;
  A d,z=(A)0;

  if(4>(slen=hb->put()-hb->get()))
  {
    if(0>readTheBuffer(hb,4-slen)) return (A)0;
    if(4>(slen=hb->put()-hb->get())) return (A)0;

    slen=longAt(hb->get());
    if(0>=slen)
    {
      static char fmt[]="\343 IPC warning: zero-length string message.  slen=%d [%d]\n";
      Warn(fmt,	slen,handle());
      hb->reset();
      turnInReadOff();
      return (A)0;
    }
    d=gv(Ct,slen);
    db->minofbuffer((C *)d); db->get(db->minofbuffer());
    db->put((C *)(d->p)); db->maxofbuffer(db->put()+slen);
  }
  if(0>readTheBuffer(db,db->maxofbuffer()-db->put())) return (A)0;
  if(db->put()==db->maxofbuffer())
  {
    z=(A)db->minofbuffer();
    hb->reset();
    db->minofbuffer(0);
    db->clear();
    return z;
  }
  return (A)0;
}
