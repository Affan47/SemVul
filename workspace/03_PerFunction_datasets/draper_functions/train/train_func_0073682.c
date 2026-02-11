penetrationDepthForFixedBoxFixedPlane(
    const Box&          box,
    const Plane&        plane,
    Array<Vector3>&     contactPoints,
    Array<Vector3>&     contactNormals) {

    Vector3 N;
    double d;

    plane.getEquation(N, d);

    contactPoints.resize(0, DONT_SHRINK_UNDERLYING_ARRAY);
    contactNormals.resize(0, DONT_SHRINK_UNDERLYING_ARRAY);

    float lowest = finf();
    for (int i = 0; i < 8; ++i) {
        const Vector3 vertex = box.corner(i);

        float x = vertex.dot(N) + (float)d;

        if (x <= 0) {

            contactPoints.append(vertex);
            contactNormals.append(-N);
        }

        lowest = min(lowest, x);
    }


    return -lowest;
}
