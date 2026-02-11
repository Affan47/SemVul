mapIn(C *name,I mode){
  int fd=-1; I z;
  int tmode = mode ;
  C*t=0;

  Q(!name||BEAM_RO>mode||BEAM_LOCAL<mode,9);
#if (_MIPS_SZLONG == 64) || defined(__alpha) || defined(__sparcv9) || defined(_ia64)

  t = findMapped64FileName(name, (BEAM_RW==tmode)) ;
  if (!t)
    t = findMapped32FileName(name, (BEAM_RW==tmode)) ;
#else
  t = findMapped32FileName(name, (BEAM_RW==tmode)) ;
#endif
  Q(!t,9);
  if(dbg_tb)beamtrc(t,1,tmode);
  ERR(t,fd=loopen(t,BEAM_RW==tmode?O_RDWR:O_RDONLY,0666));
  z=mapDotMFile(fd, tmode, name, t) ;
  if(z && dbg_tnan )nanbeamchk(t,(A)z);
  R z;
}
