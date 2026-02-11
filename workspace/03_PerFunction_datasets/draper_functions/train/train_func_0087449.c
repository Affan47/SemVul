coord_delta(const coord_t *coord1, const coord_t *coord2)
{
    double x = coord1->sin_lat * coord2->sin_lat + coord1->cos_lat * coord2->cos_lat * cos(coord1->lon - coord2->lon);
    return x < 1.0 ? acos(x) : 0.0;

}
