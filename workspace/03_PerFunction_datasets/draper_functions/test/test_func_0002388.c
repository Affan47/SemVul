red_make_up_vert(short* tl, const short* gtl, int y, int w, int h) {

  if (y<h-1)
    for (int x=1; x<w; x+=2)
      tl[y*w+x] = interpolate(tl[y*w+x-w],tl[y*w+x+w],gtl[y*w+x],gtl[y*w+x-w],gtl[y*w+x+w]);
  else
    for (int x=1; x<w; x+=2)
      tl[y*w+x] = tl[(y-1)*w+x];
}
