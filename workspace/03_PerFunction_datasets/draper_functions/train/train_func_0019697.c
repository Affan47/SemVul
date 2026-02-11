randomSurfacePoint() const {
    Vector3 extent = hi - lo;
    float aXY = extent.x * extent.y;
    float aYZ = extent.y * extent.z;
    float aZX = extent.z * extent.x;

    float r = (float)uniformRandom(0.0f, aXY + aYZ + aZX);


    float d = ((float)uniformRandom(0, 1) < 0.5f) ? 0.0f : 1.0f;


    if (r < aXY) {
        return
            lo +
            Vector3(
                (float)uniformRandom(0.0f, extent.x),
                (float)uniformRandom(0.0f, extent.y),
                d * extent.z);
    } else if (r < aYZ) {
        return
            lo +
            Vector3(
                d * extent.x,
                (float)uniformRandom(0, extent.y),
                (float)uniformRandom(0, extent.z));
    } else {
        return
            lo +
            Vector3(
                (float)uniformRandom(0, extent.x),
                d * extent.y,
                (float)uniformRandom(0, extent.z));
    }
}
