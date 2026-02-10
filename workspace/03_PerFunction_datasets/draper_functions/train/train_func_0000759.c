getRandomSurfacePoint(Vector3& p, Vector3& N) const {
    float h = height();
    float r = radius();


    float capRelArea  = square(r) / 2.0f;
    float sideRelArea = r * h;

    float r1 = uniformRandom(0, capRelArea * 2 + sideRelArea);

    if (r1 < capRelArea * 2) {


        float a = uniformRandom(0, (float)twoPi());
        float r2 = sqrt(uniformRandom(0, 1)) * r;
        p.x = cos(a) * r2;
        p.z = sin(a) * r2;

        N.x = 0;
        N.z = 0;
        if (r1 < capRelArea) {

            p.y = h / 2.0f;
            N.y = 1;
        } else {

            p.y = -h / 2.0f;
            N.y = -1;
        }
    } else {

        float a = uniformRandom(0, (float)twoPi());
        N.x = cos(a);
        N.y = 0;
        N.z = sin(a);
        p.x = N.x * r;
        p.z = N.y * r;
        p.y = uniformRandom(-h / 2.0f, h / 2.0f);
    }


    CoordinateFrame cframe;
    getReferenceFrame(cframe);

    p = cframe.pointToWorldSpace(p);
    N = cframe.normalToWorldSpace(N);
}
