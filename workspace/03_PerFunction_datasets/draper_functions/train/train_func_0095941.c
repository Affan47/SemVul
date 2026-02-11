getReferenceFrame(CoordinateFrame& cframe) const {
    cframe.translation = center();

    Vector3 Y = (p1 - p2).direction();
    Vector3 X = (abs(Y.dot(Vector3::unitX())) > 0.9) ? Vector3::unitY() : Vector3::unitX();
    Vector3 Z = X.cross(Y).direction();
    X = Y.cross(Z);
    cframe.rotation.setColumn(0, X);
    cframe.rotation.setColumn(1, Y);
    cframe.rotation.setColumn(2, Z);
}
