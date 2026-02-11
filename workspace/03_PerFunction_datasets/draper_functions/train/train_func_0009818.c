Manipulating (Event& e) {
  if (!_graphic)
    return DragManip::Manipulating(e);

  if (e.eventType == MotionEvent) {
    Constrain(e);
    IntCoord trackx, tracky;
    _r2->GetTrack(trackx, tracky);
    if (e.x!=trackx || e.y!=tracky) {
      _viewer->GetDamage()->Incur(_graphic);
      Track(e.x, e.y);
      _viewer->GetDamage()->Incur(_graphic);
      _viewer->Update();
    }

  } else if (e.eventType == UpEvent) {

    _viewer->GetDamage()->Incur(_graphic);
    if (_notrans)
      _graphic->SetTransformer(nil);
    else
      *_graphic->GetTransformer() = *_origtrans;
    _graphic->uncacheParents();
    _r = _r2;
    return false;
  }
  return true;
}
