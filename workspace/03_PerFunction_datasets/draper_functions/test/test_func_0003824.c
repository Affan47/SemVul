rfbScreenCleanup(rfbScreenInfoPtr screen)
{
  rfbClientIteratorPtr i=rfbGetClientIterator(screen);
  rfbClientPtr cl,cl1=rfbClientIteratorNext(i);
  while(cl1) {
    cl=rfbClientIteratorNext(i);
    rfbClientConnectionGone(cl1);
    cl1=cl;
  }
  rfbReleaseClientIterator(i);

#define FREE_IF(x) if(screen->x) free(screen->x)
  FREE_IF(colourMap.data.bytes);
  FREE_IF(underCursorBuffer);
  TINI_MUTEX(screen->cursorMutex);
  if(screen->cursor && screen->cursor->cleanup)
    rfbFreeCursor(screen->cursor);

#ifdef LIBVNCSERVER_HAVE_LIBZ
  rfbZlibCleanup(screen);
#ifdef LIBVNCSERVER_HAVE_LIBJPEG
  rfbTightCleanup(screen);
#endif


  while (screen->scaledScreenNext!=NULL)
  {
      rfbScreenInfoPtr ptr;
      ptr = screen->scaledScreenNext;
      screen->scaledScreenNext = ptr->scaledScreenNext;
      free(ptr->frameBuffer);
      free(ptr);
  }

#endif
  free(screen);
}
