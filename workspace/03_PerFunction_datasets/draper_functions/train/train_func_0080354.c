GSinit(GopherObj *gs)
{
     GSsetType(gs, '\0');

     STRinit(gs->Title);
     STRinit(gs->Selstr);
     STRinit(gs->Host);
     if (GSgetLocalFile(gs) != NULL)
	  unlink(GSgetLocalFile(gs));
     STRinit(gs->Localfile);
     STRinit(gs->Localview);

     gs->ttl = -1;
     gs->iPort = 0;
     GSsetNum(gs, 0);
     GSsetWeight(gs, 0);

     GSsetGplus(gs,FALSE);
     GSsetAsk(gs, FALSE);

     if (gs->url != NULL)
	  URLdestroy(gs->url);
     gs->url = NULL;
     GSplusInit(gs);
}
