unmap() {
  WindowRep& w = *rep();
  if (w.map_pending_ || is_mapped()) {
    DisplayRep& d = *w.display_->rep();
    w.glyph_->undraw();
    XUnmapWindow(w.dpy(), w.xwindow_);
    d.wtable_->remove(w.xwindow_);
    d.remove(this);
    w.canvas_->rep()->clear_damage();
    w.unmapped_ = true;
    w.wm_mapped_ = false;


    w.map_pending_ = false;
  }
}
