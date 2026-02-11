CreateWindow(int x,int y, int w, int h)
{
  XGCValues gcv;
  unsigned long gcm;


  wm_del_win = XInternAtom(dpy,"WM_DELETE_WINDOW",False);
  _XA_WM_PROTOCOLS = XInternAtom (dpy, "WM_PROTOCOLS", False);

  mysizehints.flags = PWinGravity| PResizeInc | PBaseSize |
    PMaxSize | PMinSize | USSize | USPosition;

  mysizehints.width_inc = 1;
  mysizehints.height_inc = 1;
  mysizehints.base_height = BAR_WIDTH+PAD_WIDTH3;
  mysizehints.base_width = BAR_WIDTH+PAD_WIDTH3;

  Width = w/Reduction_H + BAR_WIDTH + PAD_WIDTH3;
  Height = h/Reduction_V + BAR_WIDTH + PAD_WIDTH3;
  target_width = w;
  target_height = h;
  mysizehints.width = Width;
  mysizehints.height = Height;
  mysizehints.x = x;
  mysizehints.y = y;
  mysizehints.max_width = w + BAR_WIDTH + PAD_WIDTH3;
  mysizehints.max_height = h + BAR_WIDTH + PAD_WIDTH3;

  mysizehints.win_gravity = NorthWestGravity;

  if(d_depth < 2)
    {
      back_pix = GetColor("black");
      fore_pix = GetColor("white");
      hilite_pix = back_pix;
      shadow_pix = fore_pix;
    }
  else
    {
      back_pix = GetColor(BackColor);
      fore_pix = GetColor(ForeColor);
      hilite_pix = GetHilite(fore_pix);
      shadow_pix = GetShadow(fore_pix);

    }

  main_win = XCreateSimpleWindow(dpy,Root,mysizehints.x,mysizehints.y,
				 mysizehints.width,mysizehints.height,
				 0,fore_pix,back_pix);
  XSetWMProtocols(dpy,main_win,&wm_del_win,1);

  XSetWMNormalHints(dpy,main_win,&mysizehints);
  XSelectInput(dpy,main_win,MW_EVENTS);
  change_window_name(MyName);

  holder_win = XCreateSimpleWindow(dpy,main_win,PAD_WIDTH3,PAD_WIDTH3,
				   mysizehints.width-BAR_WIDTH -PAD_WIDTH3,
				   mysizehints.height-BAR_WIDTH-PAD_WIDTH3,
				   0,fore_pix,back_pix);
  XMapWindow(dpy,holder_win);
  gcm = GCForeground|GCBackground;
  gcv.foreground = hilite_pix;
  gcv.background = fore_pix;
  ReliefGC = XCreateGC(dpy, Root, gcm, &gcv);

  gcm = GCForeground|GCBackground;
  gcv.foreground = shadow_pix;
  gcv.background = fore_pix;
  ShadowGC = XCreateGC(dpy, Root, gcm, &gcv);

  _XA_WM_COLORMAP_WINDOWS = XInternAtom (dpy, "WM_COLORMAP_WINDOWS", False);
 }
