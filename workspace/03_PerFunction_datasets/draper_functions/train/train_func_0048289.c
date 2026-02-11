show() {
  Fl_Double_Window::show();
  if (overlay_ && overlay_ != this) overlay_->show();
}
