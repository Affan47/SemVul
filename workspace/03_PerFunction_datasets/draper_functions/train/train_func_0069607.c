flush(int eraseoverlay) {
  make_current();
  Fl_X *myi = Fl_X::i(this);
  if (!myi) return;
  if (!myi->other_xid) {
#if USE_XDBE
    if (can_xdbe()) {
      myi->other_xid = XdbeAllocateBackBufferName(fl_display, fl_xid(this), XdbeCopied);
      myi->backbuffer_bad = 1;
    } else
#endif
#if defined(USE_X11) || defined(WIN32)
    myi->other_xid = fl_create_offscreen(w(), h());
    clear_damage(FL_DAMAGE_ALL);
#elif defined(__APPLE_QUARTZ__)
    if (force_doublebuffering_) {
      myi->other_xid = fl_create_offscreen(w(), h());
      clear_damage(FL_DAMAGE_ALL);
    }
#else
# error unsupported platform
#endif
  }
#if USE_XDBE
  if (use_xdbe) {
    if (myi->backbuffer_bad || eraseoverlay) {

      if (myi->region) {XDestroyRegion(myi->region); myi->region = 0;}
      clear_damage(FL_DAMAGE_ALL);
      myi->backbuffer_bad = 0;
    }


    if (damage()) {
      fl_clip_region(myi->region); myi->region = 0;
      fl_window = myi->other_xid;
      draw();
      fl_window = myi->xid;
    }


    XdbeSwapInfo s;
    s.swap_window = fl_xid(this);
    s.swap_action = XdbeCopied;
    XdbeSwapBuffers(fl_display, &s, 1);
    return;
  } else
#endif
  if (damage() & ~FL_DAMAGE_EXPOSE) {
    fl_clip_region(myi->region); myi->region = 0;
#ifdef WIN32
    HDC _sgc = fl_gc;
    fl_gc = fl_makeDC(myi->other_xid);
    int save = SaveDC(fl_gc);
    fl_restore_clip();
    draw();
    RestoreDC(fl_gc, save);
    DeleteDC(fl_gc);
    fl_gc = _sgc;


#elif defined(__APPLE__)
    if ( myi->other_xid ) {
      fl_begin_offscreen( myi->other_xid );
      fl_clip_region( 0 );
      draw();
      fl_end_offscreen();
    } else {
      draw();
    }
#else
    fl_window = myi->other_xid;
    draw();
    fl_window = myi->xid;
#endif
  }
  if (eraseoverlay) fl_clip_region(0);


  int X,Y,W,H; fl_clip_box(0,0,w(),h(),X,Y,W,H);
  if (myi->other_xid) fl_copy_offscreen(X, Y, W, H, myi->other_xid, X, Y);
}
