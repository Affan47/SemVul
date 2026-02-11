nxt_screenshot(nxt_t *nxt,char buf[64][100]) {
  char screen[8][100];
  int modid,x,y;
  if ((modid = nxt_mod_get_id(nxt,NXT_DISPLAY_MODFILE))!=-1) {
    nxt_mod_read(nxt,modid,screen,NXT_DISPLAY_BITMAP,800);
    for (y=0;y<64;y++) {
      for (x=0;x<100;x++) buf[y][x] = screen[y/8][x]&(1<<(y%8));
    }
    return 0;
  }
  else return -1;
}
