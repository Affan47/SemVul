gxdsgl (void) {
gaint i;
  if (dblmode) {
    gxrswd(1);
    for (i=0; i<512; i++) { obj[i].type=-1; obj2[i].type = -1;}
    obnum = 0;  obnum2 = 0;
    XFreePixmap (display, pmap);
    drwbl = win;
  }
  dblmode = 0;
  return;
}
