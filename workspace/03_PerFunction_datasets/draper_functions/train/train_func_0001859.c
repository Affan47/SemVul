readBurst(void)
{
  ipcWarn(wrnlvl(),"%t pA_Connection::readBurst\n");
  MSBuffer bbuff;
  A d,z=(A)0;
  I slen=readFileLength(),slen1,n,s,count;
  if(-1==slen)R(A)0;
  if(0==slen)
  {
    static char fmt[]="\343 IPC warning: pA::ReadBurst: read event with no data [%d]\n";
    Warn(fmt, handle());
  }


  slen1=slen?slen:4;
  bbuff.minofbuffer(mab(slen1));
  bbuff.maxofbuffer(bbuff.minofbuffer()+slen1);
  bbuff.reset();
  if(0>(n=readTheBuffer(&bbuff,slen1))) {mfbuffer(&bbuff); R(A)0;}
  if(0==n&&0==slen) {turnInReadOff(); mfbuffer(&bbuff); R(A)0;}

  d=getAobjFromBuffer(&bbuff);
  if((A)0==d){mfbuffer(&bbuff); R(A)0;}


  count=1;
  for(C *cp=bbuff.get();cp<bbuff.put();cp+=s)
  {
    s=longAt(cp);
    cp+=sizeof(long);
    if(s<=bbuff.put()-cp)++count;
  }


  z=gv(Et,count);
  for(int i=0;i<count;++i)z->p[i]=(I)aplus_nl;
  int idx=0;
  z->p[idx++]=(I)d;


  while(idx<count)
  {
    d=getAobjFromBuffer(&bbuff);
    if((A)0==d)break;
    z->p[idx++]=(I)d;
  }
  if(idx<count)
  {
    ipcWarn(wrnlvl(),"%t burst mode aborted.  Possible data loss.\n");
  }


  if(bbuff.get()==bbuff.put())turnInReadOff();
  else
  {
    d=getAobjFromBuffer(&bbuff);
    if((A)0!=d || bbuff.get()!=bbuff.put())
    {
      ipcWarn(wrnlvl(),"%t burst buffer not cleared: %d %d %d\n",
	    d,bbuff.get(),bbuff.put());
    }
  }


  mfbuffer(&bbuff);

  return z;
}
