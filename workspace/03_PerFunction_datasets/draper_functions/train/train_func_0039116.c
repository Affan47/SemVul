destroyiconicon(Icon *i)
{
  if(i->innerwin) {
    XUnmapWindow(dpy, i->innerwin);
    XReparentWindow(dpy, i->innerwin, i->scr->root, i->x+4, i->y+4);
    XRemoveFromSaveSet(dpy, i->innerwin);
    i->innerwin=None;
  }
  i->iconpm = i->secondpm = None;
}
