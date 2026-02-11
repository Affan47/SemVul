VectorAngle(double *pos_i, double *pos_j, double *pos_k)
  {


    double ij[3], jk[3];
    VectorSubtract(pos_i, pos_j, ij);
    VectorSubtract(pos_k, pos_j, jk);


    double l_ij, l_jk;
    l_ij = VectorLength(ij);
    l_jk = VectorLength(jk);

    if (IsNearZero(l_ij) || IsNearZero(l_jk)) {
      return 0.0;
    }


    VectorDivide (ij, l_ij, ij);
    VectorDivide (jk, l_jk, jk);


    double c1[3];
    VectorCross(ij, jk, c1);
    double length = VectorLength(c1);
    if (IsNearZero(length)) {
      return 0.0;
    }


    double cos_ijk = VectorDot(ij, jk);
    double angle_ijk;
    if (cos_ijk > 1.0) {
      angle_ijk = 0.0;
      cos_ijk = 1.0;
    } else if (cos_ijk < -1.0) {
      angle_ijk = 180.0;
      cos_ijk = -1.0;
    } else {
      angle_ijk = RAD_TO_DEG * acos(cos_ijk);
    }

    return angle_ijk;
  }
