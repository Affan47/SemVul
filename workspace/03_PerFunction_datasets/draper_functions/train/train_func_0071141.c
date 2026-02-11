ep_fcatalog(afn)A afn;
{
  int fd;
  A z=aplus_nl;
  C *fname;
  Z C *cmdstr="fcatalog";

  fd=zretrieveInitFile(afn,cmdstr,&fname);
  if(-1==fd) R z;
  if(!Opts.pieces) z=zretrieveCatalog();
  else z=zretrievePieces();
  zretrieveUnmapFile(fd);
  zretrieveCleanup();
  if(dbg_tpack)packtrc(fname,cmdstr,0);
  R z;
}
