R3Contains(const R3Ray& ray, const R3Point& point)
{

    if (ray.IsZero()) return FALSE;
    else return RNIsZero(R3Distance(ray, point));
}
