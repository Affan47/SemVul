AngleOrder(const vector3 &a, const vector3 &b, const vector3 &c, const vector3 &center)
  {
    vector3 t, u, v;
    t = a - center;
    t.normalize();
    u = b - center;
    u.normalize();
    v = c - center;
    v.normalize();
    return TriangleSign(t, u, v) > 0;
  }
