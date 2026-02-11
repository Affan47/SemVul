ewmh_change_window_type(const FXWindow * window,FXuint kind) {
#ifndef WIN32
  static Atom net_wm_window_type               = None;
  static Atom net_wm_window_type_menu          = None;
  static Atom net_wm_window_type_dropdown_menu = None;
  static Atom net_wm_window_type_popup_menu    = None;
  static Atom net_wm_window_type_combo         = None;
  static Atom net_wm_window_type_tooltip       = None;
  static Atom net_wm_window_type_dialog        = None;
  static Atom net_wm_window_type_normal        = None;

  FXASSERT(window->getApp());
  FXASSERT(window->getApp()->getDisplay());
  FXASSERT(window->id());

  if (net_wm_window_type==None){
    net_wm_window_type               = XInternAtom((Display*)window->getApp()->getDisplay(),"_NET_WM_WINDOW_TYPE",False);
    net_wm_window_type_menu          = XInternAtom((Display*)window->getApp()->getDisplay(),"_NET_WM_WINDOW_TYPE_MENU",False);
    net_wm_window_type_dropdown_menu = XInternAtom((Display*)window->getApp()->getDisplay(),"_NET_WM_WINDOW_TYPE_DROPDOWN_MENU",False);
    net_wm_window_type_popup_menu    = XInternAtom((Display*)window->getApp()->getDisplay(),"_NET_WM_WINDOW_TYPE_POPUP_MENU",False);
    net_wm_window_type_combo         = XInternAtom((Display*)window->getApp()->getDisplay(),"_NET_WM_WINDOW_TYPE_COMBO",False);
    net_wm_window_type_tooltip       = XInternAtom((Display*)window->getApp()->getDisplay(),"_NET_WM_WINDOW_TYPE_TOOLTIP",False);
    net_wm_window_type_dialog        = XInternAtom((Display*)window->getApp()->getDisplay(),"_NET_WM_WINDOW_TYPE_DIALOG",False);
    net_wm_window_type_normal        = XInternAtom((Display*)window->getApp()->getDisplay(),"_NET_WM_WINDOW_TYPE_NORMAL",False);
    }


  unsigned int ntypes=0;
  Atom types[3]={0};

  switch(kind) {
    case WINDOWTYPE_DIALOG          : types[0]=net_wm_window_type_dialog;
                                      ntypes=1;
                                      break;
    case WINDOWTYPE_COMBO           : types[0]=net_wm_window_type_combo;
                                      types[1]=net_wm_window_type_dropdown_menu;
                                      types[2]=net_wm_window_type_menu;
                                      ntypes=3;
                                      break;
    case WINDOWTYPE_POPUP_MENU      : types[0]=net_wm_window_type_popup_menu;
                                      types[1]=net_wm_window_type_menu;
                                      ntypes=2;
                                      break;
    case WINDOWTYPE_DROPDOWN_MENU   : types[0]=net_wm_window_type_dropdown_menu;
                                      types[1]=net_wm_window_type_menu;
                                      ntypes=2;
                                      break;
    case WINDOWTYPE_TOOLTIP         : types[0]=net_wm_window_type_tooltip;
                                      ntypes=1;
                                      break;
    default                         : types[0]=net_wm_window_type_normal;
                                      ntypes=1;
                                      break;
    }


  XChangeProperty((Display*)window->getApp()->getDisplay(),window->id(),net_wm_window_type,XA_ATOM,32,PropModeReplace,(unsigned char*)&types,ntypes);
#endif
  }
