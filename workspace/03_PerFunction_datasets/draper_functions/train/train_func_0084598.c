CreateManipulator (
    Viewer* v, Event& e, Transformer* rel
) {
  Coord x[1], y[1];
  x[0] = e.x;
  y[0] = e.y;
  GrowingVertices* rub = new GrowingPolygon(nil, nil, x, y, 1, -1, HANDLE_SIZE
        );
  Manipulator* m =
    new VertexManip(v, rub, rel, this);
  return m;
}
