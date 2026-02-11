NotifyLater() {
  Observable::notify();

  if (OverlayUnidraw::deferred_notifications())
    _notify_deferred = 1;
  else
    GraphicComp::Notify();
}
