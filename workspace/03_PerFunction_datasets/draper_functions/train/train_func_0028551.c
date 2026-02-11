sendpagewithxcmd(const char *buf, int size, const char *penc, const char *cmd){
  const char *tmpdir, *pv, *ext, *fmt;
  char iname[URIBUFSIZ], oname[URIBUFSIZ], cbuf[URIBUFSIZ], *rbuf;
  int rnd, pid, rsiz;
  struct stat sbuf;
  if(ESTPATHCHR == '/' && stat("/tmp", &sbuf) == 0){
    tmpdir = "/tmp";
  } else if(ESTPATHCHR == '\\' &&
            ((pv = getenv("TMP")) != NULL || (pv = getenv("TEMP")) != NULL) &&
            stat(pv, &sbuf) == 0){
    tmpdir = pv;
  } else {
    tmpdir = ESTCDIRSTR;
  }
  ext = NULL;
  if(!(pv = strrchr(p_url, ESTPATHCHR))) pv = p_url;
  if((pv = strrchr(pv, ESTEXTCHR)) != NULL) ext = pv;
  if(!ext || strlen(ext) >= 32 || strchr(ext, '"') || strchr(ext, '\\')) ext = "";
  rnd = dpouterhash(p_url, -1) & 0xffff;
  pid = (int)getpid() & 0xffff;
  sprintf(iname, "%s%cxcmd-in-%04X%04X%s", tmpdir, ESTPATHCHR, pid, rnd, ext);
  sprintf(oname, "%s%cxcmd-out-%04X%04X%cest", tmpdir, ESTPATHCHR, pid, rnd, ESTEXTCHR);
  fmt = DRAFTCMD;
  if(cbstrfwmatch(cmd, "T@")){
    fmt = TEXTCMD;
    cmd += 2;
  } else if(cbstrfwmatch(cmd, "H@")){
    fmt = HTMLCMD;
    cmd += 2;
  } else if(cbstrfwmatch(cmd, "M@")){
    fmt = MIMECMD;
    cmd += 2;
  }
  cbwritefile(iname, buf, size);
  sprintf(cbuf, "%s \"%s\" \"%s\"", cmd, iname, oname);
  system(cbuf);
  if((rbuf = cbreadfile(oname, &rsiz)) != NULL){
    if(fmt == DRAFTCMD){
      sendpagefromdraft(rbuf, rsiz, NULL);
    } else if(fmt == TEXTCMD){
      sendpagefromtext(rbuf, rsiz, NULL);
    } else if(fmt == HTMLCMD){
      sendpagefromhtml(rbuf, rsiz, NULL);
    } else if(fmt == MIMECMD){
      sendpagefrommime(rbuf, rsiz, NULL);
    }
    free(rbuf);
  }
  unlink(oname);
  unlink(iname);
}
