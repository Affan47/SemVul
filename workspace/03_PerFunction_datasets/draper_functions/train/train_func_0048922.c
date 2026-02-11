dbg_mfrsf(void)
{
  I n=0;
  A z,modes,args,fnames,addrs,refcnts,bytes;
  MFInfo *p;
  z=gv(Et,2);
  z->p[0]=(I)gvi(Et,6,MS(si("mode")),MS(si("arg")),MS(si("fname")),
		 MS(si("addr")),MS(si("refcnt")),MS(si("bytes")));
  if(MappedFileArray){DO(maxMFAindex,if(MappedFileArray[i].a)++n);}
  modes=gv(It,n);
  args=gv(Et,n);
  fnames=gv(Et,n);
  addrs=gv(It,n);
  refcnts=gv(It,n);
  bytes=gv(It,n);
  n=0;
  if(MappedFileArray)
  {
    DO(maxMFAindex,
       if(MappedFileArray[i].a){p=MappedFileArray+i;
				modes->p[n]=p->w;
				args->p[n]=(I)gsv(0,p->s);
				fnames->p[n]=(I)gsv(0,p->t);
				addrs->p[n]=p->a;
				refcnts->p[n]=p->c;
				bytes->p[n]=p->n;
				n++;});
  }
  z->p[1]=(I)gvi(Et,6,modes,args,fnames,addrs,refcnts,bytes);
  R z;
}
