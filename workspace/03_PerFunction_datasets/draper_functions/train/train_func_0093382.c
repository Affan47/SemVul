loadgame(void)

{
  genfile loadfile;
  long size;
  uchar *gs;
  char *errstr;

  loadfile=get_user_file(2);
  if (!filevalid(loadfile,fSAV)) {
    writeln("Unable to open file.");
    return 0;
  }
  size=binsize(loadfile);
  if (size==-1) {
    writeln("Could not access file.");
    readclose(loadfile);
    return 0;
  }
  gs=rmalloc(size);
  if (!binread(loadfile,gs,size,1,&errstr)) {
    writeln("Error reading file.");
    rfree(gs);readclose(loadfile);
    return 0;
  }
  readclose(loadfile);
  if (size!=gs[0]+(((long)gs[1])<<8)+(((long)gs[2])<<16)+(((long)gs[3])<<24)){
    if (size==gs[0]+(((long)gs[1])<<8)) {

      gs=rrealloc(gs,size+2);
      memmove(gs+4,gs+2,size-2);
      gs[2]=gs[3]=0;
    } else {
      writeln("Save file corrupted or invalid.");
      rfree(gs);
      return 0;
    }
  }
  putstate(gs);
  rfree(gs);
  set_statline();
  look_room();
  return 1;
}
