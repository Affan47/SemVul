MakeRubberband(IntCoord x, IntCoord y) {
  Coord l, r, b, t;
  Viewer* v = GetViewer();
  GetEllipse()->GetBox(l, b, r, t);
  Coord cx, cy;
  int rx, ry;
  GetEllipse()->GetOriginal(cx, cy, rx, ry);
  Rubberband* rub = new SlidingEllipse(nil, nil, l+(r-l)/2, b+(t-b)/2,
				       Math::round(rx * v->GetMagnification()),
				       Math::round(ry * v->GetMagnification()),
				       x, y);
  return rub;
}
