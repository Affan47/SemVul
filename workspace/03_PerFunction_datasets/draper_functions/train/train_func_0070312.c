resize(ButWin *win)  {
  GmpSetup  *gs = butWin_packet(win);
  Cgoban  *cg;
  int  w, h;
  int  bw, fh;
  ButEnv  *env;
  int  boxX, boxY, boxW, boxH, butX, butW, butY;
  GoStone  s;
  GmpSetupPlayer  *p;

  assert(MAGIC(gs));
  cg = gs->cg;
  assert(MAGIC(cg));
  env = cg->env;
  bw = butEnv_stdBw(env);
  fh = cg->fontH;
  w = butWin_w(win);
  h = butWin_h(win);

  but_resize(gs->bg, 0,0, w,h);
  butText_resize(gs->title, w/2,bw*2, fh*2);
  boxX = bw;
  boxY = bw * 3 + fh * 2;
  boxH = h - bw * 6 - fh * 4;
  goStoneIter(s)  {
    p = &gs->players[s];
    boxW = (w - bw * 2 + (int)s) / 2;
    but_resize(p->box, boxX, boxY, boxW, boxH);
    butX = boxX + bw * 2;
    butW = boxW - bw * 4;
    butY = boxY + bw * 2;
    boxX += boxW;
    but_resize(p->typeMenu, butX, butY, butW, fh * 4);
    butY += fh * 4 + bw;
    but_resize(p->strDesc1, butX, butY, butW, fh * 2);
    butY += fh * 2 + bw;
    but_resize(p->strIn1, butX, butY, butW, fh * 2);
    butY += fh * 2 + bw;
    but_resize(p->strDesc2, butX, butY, butW, fh * 2);
    butY += fh * 2 + bw;
    but_resize(p->strIn2, butX, butY, butW, fh * 2);
  }

  boxX = bw * 2;
  boxW = (w - bw * 6) / 3;
  but_resize(gs->help, boxX, boxY + boxH + bw, boxW, fh * 2);
  boxX += boxW + bw;
  boxW = (w - bw * 6) / 3 + ((w - bw * 6) % 3);
  but_resize(gs->cancel, boxX, boxY + boxH + bw, boxW, fh * 2);
  boxX += boxW + bw;
  boxW = (w - bw * 6) / 3;
  but_resize(gs->ok, boxX, boxY + boxH + bw, boxW, fh * 2);
  return(0);
}
