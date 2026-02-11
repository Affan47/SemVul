setbackground(unsigned long newbg) {
  int r;

  if (newbg == lastbackground) return;
  r= XSetWindowBackground(disp,win,newbg);
  if (!r) fail("XSetWindowBackground");
  lastbackground= newbg;
}
