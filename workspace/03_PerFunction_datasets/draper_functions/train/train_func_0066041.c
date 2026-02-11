parseFeatures() {
  ExtPatternMatcher sf,nf;
  ChessGame *cg;
  char *cand,*p;
  int n;
  bool gotdone=false;

  sf.set("%b%s=\"*\"*");
  nf.set("%b%s=%n*");
  cand=Features.getStarToken(1);

  while(1) {
    if (sf.match(cand)) {
      p=sf.getSToken(0);
      if (!strcmp(p,"myname")) {
	ComputerName[63]=0;
	g_strlcpy(ComputerName,sf.getStarToken(0),64);
	global.status->setText(ComputerName,10);
	cg=global.getGame(XBOARD_GAME);
	if (cg) {
	  g_strlcpy(cg->PlayerName[EngineWhite?0:1],ComputerName,64);
	  cg->acknowledgeInfo();
	}
      }
      cand=sf.getStarToken(1);
      continue;
    }
    if (nf.match(cand)) {
      p=nf.getSToken(0);

      if (!strcmp(p,"setboard")) {
	n=atoi(nf.getNToken(0));
	if (n) supports_setboard=true;
      }
      if (!strcmp(p,"usermove")) {
	n=atoi(nf.getNToken(0));
	if (n) requires_usermove=true;
      }

      if (!strcmp(p,"done")) {
	n=atoi(nf.getNToken(0));
	if (n)
	  gotdone=true;
	else {

	  global.status->setText(_("Engine asked more time to startup, waiting."),120);
	  if (timeout_id >= 0)
	    gtk_timeout_remove(timeout_id);


	  timeout_id=gtk_timeout_add(3600000, xb_initengine_timeout,
				     (gpointer) this);
	}

      }

      cand=nf.getStarToken(0);
      continue;
    }
    break;
  }

  if (gotdone && timeout_id >= 0) {
    gtk_timeout_remove(timeout_id);
    timeout_id=-1;
    global.status->setText(_("Engine loaded."),20);
    initEngine();
  }
}
