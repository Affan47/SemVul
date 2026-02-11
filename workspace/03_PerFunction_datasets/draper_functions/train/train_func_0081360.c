traceNormal(const Ray &ray)
{

    Hit min_hit = findHit(ray);


    if (!min_hit.object)
        return Color(0.0, 0.0, 0.0);

    Point hit = ray.at(min_hit.t);
    Vector N = min_hit.N;


    return (N + 1) / 2.0;
}
