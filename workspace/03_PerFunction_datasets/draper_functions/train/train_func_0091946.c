sym_round(double val)
{
        double n;
        double f = std::fabs(std::modf(val, &n));
        if (val >= 0) {
                if (f < 0.5) {
                        return std::floor(val);
                } else if (f > 0.5) {
                        return std::ceil(val);
                } else {
                        return (n + 1.0);
                }
        } else {
                if (f < 0.5) {
                        return std::ceil(val);
                } else if (f > 0.5) {
                        return std::floor(val);
                } else {
                        return (n - 1.0);
                }
        }
}
