multi_labeltype(
    const Fl_Label* o, int x, int y, int w, int h, Fl_Align a)
{
  Fl_Multi_Label* b = (Fl_Multi_Label*)(o->value);
  Fl_Label local = *o;
  local.value = b->labela;
  local.type = b->typea;
  int W = w; int H = h; local.measure(W, H);
  local.draw(x,y,w,h,a);
  if (a & FL_ALIGN_BOTTOM) h -= H;
  else if (a & FL_ALIGN_TOP) {y += H; h -= H;}
  else if (a & FL_ALIGN_RIGHT) w -= W;
  else if (a & FL_ALIGN_LEFT) {x += W; w -= W;}
  else {int d = (h+H)/2; y += d; h -= d;}
  local.value = b->labelb;
  local.type = b->typeb;
  local.draw(x,y,w,h,a);
}
