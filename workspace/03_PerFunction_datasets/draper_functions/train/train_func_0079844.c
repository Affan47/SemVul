isIdentity(Coord const eps) const {
    return are_near(_c[0], 1.0, eps) && are_near(_c[1], 0.0, eps) &&
           are_near(_c[2], 0.0, eps) && are_near(_c[3], 1.0, eps) &&
           are_near(_c[4], 0.0, eps) && are_near(_c[5], 0.0, eps);
}
