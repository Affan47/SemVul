syncDoWrite(void)
{
  I c,n=0;
  MSNodeItem *hp=writeList();
  MSNodeItem *np;
  MSBuffer *bp;
  MSBoolean notdone=MSTrue;

  ipcWarn(wrnlvl(), "%t pString_Connection::syncDoWrite\n");


  while(notdone&&(hp!=(np=hp->next())))
  {
    bp=(MSBuffer *)np->data();
    c=bp->put()-bp->get();
    while(c>0 && 0<(n=bp->write(fd(),c))) c-=n;
    if(bp->get() == bp->put())
    {
      delete bp;delete np;turnInWriteOff();
    }
    else
    {
      notdone=MSFalse;turnInWriteOn();
    }
    if (0 > n)
      return syncFillError("buffwrite","buffwrite returned error %d",n);
  }
  if(hp == hp->next()) return 1;
  else return 0;
}
