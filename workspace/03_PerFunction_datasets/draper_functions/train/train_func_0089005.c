display(void* item) {


  update_top();
  if (item == item_first()) {position(0); return;}

  int X, Y, W, H, Yp; bbox(X, Y, W, H);
  void* l = top_;
  Y = Yp = -offset_;
  int h1;


  if (l == item) {position(real_position_+Y); return;}


  void* lp = item_prev(l);
  if (lp == item) {position(real_position_+Y-item_quick_height(lp)); return;}

#ifdef DISPLAY_SEARCH_BOTH_WAYS_AT_ONCE


  while (l || lp) {
    if (l) {
      h1 = item_quick_height(l);
      if (l == item) {
	if (Y <= H) {
	  Y = Y+h1-H;
	  if (Y > 0) position(real_position_+Y);
	} else {
	  position(real_position_+Y-(H-h1)/2);
	}
	return;
      }
      Y += h1;
      l = item_next(l);
    }
    if (lp) {
      h1 = item_quick_height(lp);
      Yp -= h1;
      if (lp == item) {
	if ((Yp + h1) >= 0) position(real_position_+Yp);
	else position(real_position_+Yp-(H-h1)/2);
	return;
      }
      lp = item_prev(lp);
    }
  }
#else


  l = top_;
  for (; l; l = item_next(l)) {
    h1 = item_quick_height(l);
    if (l == item) {
      if (Y <= H) {
	Y = Y+h1-H;
	if (Y > 0) position(real_position_+Y);
      } else {
	position(real_position_+Y-(H-h1)/2);
      }
      return;
    }
    Y += h1;
  }

  l = lp;
  Y = -offset_;
  for (; l; l = item_prev(l)) {
    h1 = item_quick_height(l);
    Y -= h1;
    if (l == item) {
      if ((Y + h1) >= 0) position(real_position_+Y);
      else position(real_position_+Y-(H-h1)/2);
      return;
    }
  }
#endif
}
