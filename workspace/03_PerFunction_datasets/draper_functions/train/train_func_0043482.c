replaceMax(heap *hp, heapEl newEl){
  heapEl t;
  hp->h[0] = newEl;
  unint swapInd;
  unint i = 0;
  char done = 0;

  while( 2*i+1 < hp->len && !done){
    if( 2*i+2 < hp->len )
      swapInd = MAXI(hp->h[2*i+1].val, hp->h[2*i+2].val, 2*i+1, 2*i+2);
    else
      swapInd = 2*i+1;

    if(hp->h[i].val < hp->h[swapInd].val){
      t.id = hp->h[swapInd].id;
      t.val = hp->h[swapInd].val;
      hp->h[swapInd].id = hp->h[i].id;
      hp->h[swapInd].val = hp->h[i].val;
      hp->h[i].id = t.id;
      hp->h[i].val = t.val;
      i = swapInd;
    }
    else
      done = 1;
  }
}
