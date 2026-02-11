combine(const Geometry* g0, const Geometry* g1,
                                    const Geometry* g2)
{
    std::vector<Geometry*> geoms;
    geoms.push_back(const_cast<Geometry*>(g0));
    geoms.push_back(const_cast<Geometry*>(g1));
    geoms.push_back(const_cast<Geometry*>(g2));

    GeometryCombiner combiner(geoms);
    return combiner.combine();
}
