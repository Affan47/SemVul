butRcur_redraw(ButEnv *env, int winId, int x,int y, int w,int h)  {
  int  i;

  if (winId == -2)
    return;
  for (i = 0;  i < env->numPartners;  ++i)  {
    if (env->partners[i])  {
      if (butRnet_valid(env->partners[i]) &&
	  (winId == env->partners[i]->rc.winId))
	butRcur_hideForRedraw(&env->partners[i]->rc, winId, x,y, w,h);
    }
  }
}
