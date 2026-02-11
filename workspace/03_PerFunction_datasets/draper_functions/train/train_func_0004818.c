D_box(double x1, double y1, double x2, double y2)
{
    double l = min(x1, x2);
    double r = max(x1, x2);
    double b = min(y1, y2);
    double t = max(y1, y2);
    int li = round(D_u_to_d_col(l));
    int ri = round(D_u_to_d_col(r));
    int bi = round(D_u_to_d_row(b));
    int ti = round(D_u_to_d_row(t));

    R_box_abs(li, ti, ri, bi);
}
