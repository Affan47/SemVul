resetgame()
{
  gameover=false;
  winner=false;
  {
    uint8 i;
    for (i=0;i<NUMSHOTS;++i) shots[i].x=-1;
  };
  ship=40;
  shipmove=0;
  {
    uint8 x,y;
    for (x=0;x<8;++x) {
      for (y=0;y<5;++y) {
	struct alien_t *a = &aliens[y*8+x];
	a->x=x*7+12;
	a->y=y*2;
	a->xadd = ( (x%2) ^ (y%2) ) ? -1 : 1;
      };
    };
  };
}
