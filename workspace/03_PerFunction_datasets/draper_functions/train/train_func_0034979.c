is_scale(Coord const eps) const {
    return ( (fabs(_c[0] - 1.0) > eps || fabs(_c[3] - 1.0) > eps) &&
             fabs(_c[1])       < eps &&
             fabs(_c[2])       < eps   );
}
