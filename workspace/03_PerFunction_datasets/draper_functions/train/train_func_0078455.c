isPointInsideRectangle(
    const Vector3& v0,
    const Vector3& v1,
    const Vector3& v2,
    const Vector3& v3,
    const Vector3& normal,
    const Vector3& point) {

    return isPointInsideTriangle(v0, v1, v2, normal, point) ||
           isPointInsideTriangle(v2, v3, v0, normal, point);
}
