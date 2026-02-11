mergeTJPFlags() {
  _tjp.clear ();
  if (_next) {
    _next->mergeTJPFlags ();
    _tjp.merge (_next->tjp ());
  }
  for (int a = 0; a < _before.length(); a++) addTJPFlags(*_before[a]);
  if (_around)  {
    addTJPFlags(*_around);
    if (_conditional_around) {
      _tjp.conditional ();
    }
  }
  for (int a = 0; a < _after.length(); a++) addTJPFlags(*_after[a]);
}
