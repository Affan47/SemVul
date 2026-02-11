animate_y_axis(Gameboard *g, buttonstate *b, GdkRectangle *r){
  int ret=0;

  if(b->y_target != b->y){
    ret=1;
    expand_rectangle_button(b,r);
    if(b->rollover)
      expand_rectangle_rollover(g,b,r);

    if(b->y_target > b->y){
      b->y+=DEPLOY_DELTA;
      if(b->y>b->y_target)b->y=b->y_target;
    }else{
      b->y-=DEPLOY_DELTA;
      if(b->y<b->y_target)b->y=b->y_target;
    }
    expand_rectangle_button(b,r);
    if(b->rollover)
      expand_rectangle_rollover(g,b,r);
  }

  if(b->alphad != b->y_active - b->y){
    double alpha=0;
    if(b->y_inactive>b->y_active){
      if(b->y<=b->y_active)
	alpha=1.;
      else if (b->y>=b->y_inactive)
	alpha=0.;
      else
	alpha = (double)(b->y_inactive-b->y)/(b->y_inactive-b->y_active);
    }else if (b->y_inactive<b->y_active){
      if(b->y>=b->y_active)
	alpha=1.;
      else if (b->y<=b->y_inactive)
	alpha=0.;
      else
	alpha = (double)(b->y_inactive-b->y)/(b->y_inactive-b->y_active);
    }
    if(alpha != b->alpha){
      ret=1;
      expand_rectangle_button(b,r);
      b->alpha=alpha;
    }
    b->alphad = b->y_active - b->y;
  }

  return ret;
}
