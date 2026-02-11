fit_local_plane_by_pos(gint n,
                       const gint *xp, const gint *yp, const gdouble *z,
                       gdouble *bx, gdouble *by)
{
    gdouble m[12], b[4];
    gint i;

    memset(m, 0, 6*sizeof(gdouble));
    memset(b, 0, 4*sizeof(gdouble));
    for (i = 0; i < n; i++) {
        m[1] += xp[i];
        m[2] += xp[i]*xp[i];
        m[3] += yp[i];
        m[4] += xp[i]*yp[i];
        m[5] += yp[i]*yp[i];
        b[0] += z[i];
        b[1] += xp[i]*z[i];
        b[2] += yp[i]*z[i];
        b[3] += z[i]*z[i];
    }
    m[0] = n;
    memcpy(m + 6, m, 6*sizeof(gdouble));
    if (gwy_math_choleski_decompose(3, m))
        gwy_math_choleski_solve(3, m, b);
    else
        b[0] = b[1] = b[2] = 0.0;

    *bx = b[1];
    *by = b[2];
    return (b[3] - (b[0]*b[0]*m[6+0] + b[1]*b[1]*m[6+2] + b[2]*b[2]*m[6+5])
            - 2.0*(b[0]*b[1]*m[6+1] + b[0]*b[2]*m[6+3] + b[1]*b[2]*m[6+4]));
}
