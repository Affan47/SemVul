blue_better_middle(short* tl, short* id, int y, int w) {
  id += (y/2)*w/2;
  tl += y*w;

  tl[0] = boundcheck((8*id[0]-tl[-w]-tl[w])/6);

  for (int x=2; x<w; x+=2)
    tl[x] = boundcheck((64*id[x/2]
			-6*tl[-w+x] -6*tl[w+x]
			-6*tl[x-1]  -6*tl[x+1]
			-tl[-w+x-1] -tl[-w+x+1]
			-tl[w+x-1]  -tl[w+x+1])/36);
}
