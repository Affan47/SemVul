zBufferTrace(const Ray &ray)
{

    Hit min_hit(std::numeric_limits<double>::infinity(),Vector());
    Object *obj = NULL;

    for (unsigned int i = 0; i < objects.size(); ++i) {
        Hit hit(objects[i]->intersect(ray));
        if (hit.t<min_hit.t) {
            min_hit = hit;
            obj = objects[i];
        }
    }


    if (!obj) return Color(0.0, 0.0, 0.0);

    double z = 1-(min_hit.t-min_t) / (max_t-min_t);
    z = (z * 0.9) + 0.1;
    return Color(z,z,z);
}
