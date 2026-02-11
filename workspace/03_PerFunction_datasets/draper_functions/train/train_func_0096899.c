flush() {
#ifdef BOXX_BUGS
  if (overlay_ && overlay_ != this && overlay_->shown()) {

    XUnmapWindow(fl_display, fl_xid(overlay_));
    Fl_Double_Window::flush(0);
    XMapWindow(fl_display, fl_xid(overlay_));
    return;
  }
#endif
  int erase_overlay = (damage()&FL_DAMAGE_OVERLAY) | (overlay_ == this);
  clear_damage((uchar)(damage()&~FL_DAMAGE_OVERLAY));
  Fl_Double_Window::flush(erase_overlay);
  if (overlay_ == this) draw_overlay();
}
