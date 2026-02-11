makeBookmarkCaption() {
  tstring t,u;
  string x, *p;
  char caption[1024], z[128];

  if (!ebm) return;

  t.set(EngineCommandLine);
  x=EngineCommandLine;
  if (x.empty()) x="<blank?>";

  p=t.token(" ");
  if (p != 0) {
    u.set(*p);
    while( (p=u.token("/")) != 0 )
      x=*p;
  }

  ebm->timecontrol.toString(z,128);
  snprintf(caption,1024,
	   _("Play %s as %s vs. %s (%s, maxdepth %d, think always: %s)"),
	   ChessGame::variantName(ebm->mode),
	   ebm->humanwhite?_("White"):
	   _("Black"),
	   x.c_str(),
	   z,
	   ebm->maxply,
	   ebm->think?_("yes"):
	              _("no"));
  ebm->caption = caption;
}
