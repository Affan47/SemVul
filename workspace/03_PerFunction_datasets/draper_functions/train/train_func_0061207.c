LookAt(const Point &pos, const Point &look, const Vector &up) {
    float m[4][4];

    m[0][3] = pos.x;
    m[1][3] = pos.y;
    m[2][3] = pos.z;
    m[3][3] = 1;


    Vector dir = Normalize(look - pos);
    if (Cross(Normalize(up), dir).Length() == 0) {
        Error("\"up\" vector (%f, %f, %f) and viewing direction (%f, %f, %f) "
              "passed to LookAt are pointing in the same direction.  Using "
              "the identity transformation.", up.x, up.y, up.z, dir.x, dir.y,
              dir.z);
        return Transform();
    }
    Vector left = Normalize(Cross(Normalize(up), dir));
    Vector newUp = Cross(dir, left);
    m[0][0] = left.x;
    m[1][0] = left.y;
    m[2][0] = left.z;
    m[3][0] = 0.;
    m[0][1] = newUp.x;
    m[1][1] = newUp.y;
    m[2][1] = newUp.z;
    m[3][1] = 0.;
    m[0][2] = dir.x;
    m[1][2] = dir.y;
    m[2][2] = dir.z;
    m[3][2] = 0.;
    Matrix4x4 camToWorld(m);
    return Transform(Inverse(camToWorld), camToWorld);
}
