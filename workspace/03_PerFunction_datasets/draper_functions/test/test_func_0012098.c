dokey(rfbBool down,rfbKeySym key,rfbClientPtr cl)
{
  if(down) {
    if(key==XK_Escape)
      rfbCloseClient(cl);
    else if(key==XK_F12)

      rfbShutdownServer(cl->screen,TRUE);
    else if(key==XK_F11)

      rfbShutdownServer(cl->screen,FALSE);
    else if(key==XK_Page_Up) {
      initBuffer((unsigned char*)cl->screen->frameBuffer);
      rfbMarkRectAsModified(cl->screen,0,0,maxx,maxy);
    } else if (key == XK_Up) {
      if (maxx < 1024) {
        if (maxx < 800) {
          newframebuffer(cl->screen, 800, 600);
        } else {
          newframebuffer(cl->screen, 1024, 768);
        }
      }
    } else if(key==XK_Down) {
      if (maxx > 640) {
        if (maxx > 800) {
          newframebuffer(cl->screen, 800, 600);
        } else {
          newframebuffer(cl->screen, 640, 480);
        }
      }
    } else if(key>=' ' && key<0x100) {
      ClientData* cd=cl->clientData;
      int x1=cd->oldx,y1=cd->oldy,x2,y2;
      cd->oldx+=rfbDrawCharWithClip(cl->screen,&radonFont,cd->oldx,cd->oldy,(char)key,0,0,cl->screen->width,cl->screen->height,0x00ffffff,0x00ffffff);
      rfbFontBBox(&radonFont,(char)key,&x1,&y1,&x2,&y2);
      rfbMarkRectAsModified(cl->screen,x1,y1,x2-1,y2-1);
    }
  }
}
