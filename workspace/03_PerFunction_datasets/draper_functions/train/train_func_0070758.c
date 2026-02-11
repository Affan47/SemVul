read_voc(fc_type fc)
{
  char linbuf[80];
  genfile vocfile;

  init_verbrec();
  vocfile=openfile(fc,fVOC,NULL,0);
  if (filevalid(vocfile,fVOC)) {
    while(readln(vocfile,linbuf,79))
      add_verbrec(linbuf,0);
    readclose(vocfile);
    finish_verbrec();
  }
}
