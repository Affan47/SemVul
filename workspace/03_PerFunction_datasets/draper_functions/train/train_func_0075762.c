ff_least_squares(ft_size N, const double x[], const double y[], double & ret_m, double & ret_q)
{
    double X = 0, X2 = 0;
    double Y = 0, Y2 = 0;
    double XY = 0;
    double x0 = x[0], y0 = y[0], x_, y_;

    for (ft_size i = 0; i < N; i++) {
        x_ = x[i] - x0;
        y_ = y[i] - y0;
        X  += x_; X2 += x_ * x_;
        Y  += y_; Y2 += y_ * y_;
        XY += x_ * y_;
    }
    double v = X2 - X*X/N;
    if (v == 0.0)
        return -EDOM;
    double c = XY - X*Y/N;
    ret_m = c / v;

    ret_q = (Y - ret_m*X) / N + (y0 - ret_m*x0);
    return 0;
}
