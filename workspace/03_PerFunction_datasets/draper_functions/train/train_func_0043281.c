is_rotation(Coord const eps) const {
    return ( fabs(_c[1]) > eps &&
             fabs(_c[2]) > eps &&
             fabs(_c[1] + _c[2]) < 2 * eps);
}
