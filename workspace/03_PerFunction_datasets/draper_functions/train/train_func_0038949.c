readOne(void)
{
  ipcWarn(wrnlvl(),"%t pRaw_Connection::readOne\n");
  MSBuffer bbuff;
  A z;
  I slen=0,slen1,rlen;
  if(-1==ioctl(fd(),FIONREAD,&slen)) {


    ipcWarn(wrnlvl(),"%t ioctl FIONREAD failed: %d\n",errno);
    resetWithError("ioctl");
    R(A)0;
  }
  if(0==slen)
  {
    Warn("\343 IPC warning: pRaw::readOne: read event with no data [%d]\n",
      handle());
    resetWithError("ioctl");
    R(A)0;
  }


  slen1=slen?slen:4;
  z=gv(Ct,slen1);
  bbuff.minofbuffer((C*)z->p);
  bbuff.maxofbuffer(bbuff.minofbuffer()+slen1);
  bbuff.reset();

  if(0>(rlen=readTheBuffer(&bbuff,slen))) {dc(z);z=(A)0;}
  else if(0>=bbuff.put()-bbuff.get()) {dc(z);z=(A)0;}
  else {z->n=z->d[0]=rlen;((C*)z->p)[rlen]='\0';}
  turnInReadOff();
  bbuff.minofbuffer(0);
  bbuff.maxofbuffer(0);
  bbuff.reset();
  R z;
}
