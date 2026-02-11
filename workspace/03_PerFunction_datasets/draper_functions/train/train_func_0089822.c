readOne(void)
{
  ipcWarn(wrnlvl(),"%t pIpc_Connection::readOne\n");
  A d,d0,d1,z;
  C *c;
  MSBuffer *hb=headBuffer();
  MSBuffer *db=readBuffer();
  I s;

  if(16>(s=hb->put()-hb->get())){
    if(0>readTheBuffer(hb,16-s)) R(A)0;
    if(16>(s=hb->put()-hb->get())) R(A)0;
    c = hb->get();
    d=gv(Et,2);
    d->p[0]=(I)(d0=gv(It,5));
    d0->p[0]=longAt(c);
    d0->p[1]=longAt(c+4);
    d0->p[2]=shortAt(c+8);
    d0->p[3]=shortAt(c+10);
    d0->p[4]=longAt(c+12);
    d->p[1]=(I)(d1=gv(Ct,s=d0->p[4]));
    db->minofbuffer((C *)(d));
    db->get(db->minofbuffer());
    db->put((C *)(d1->p));
    db->maxofbuffer(db->put()+s);
  }
  if(0>readTheBuffer(db,db->maxofbuffer()-db->put())) R(A)0;
  if(db->put() == db->maxofbuffer())
  {
    z=(A)(db->minofbuffer());
    hb->reset();
    db->minofbuffer(0);
    db->clear();
    turnInReadOff();
    R z;
  }
  R(A)0;
}
