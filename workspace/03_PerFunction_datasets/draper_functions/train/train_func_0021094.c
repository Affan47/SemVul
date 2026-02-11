log1pexp(double x) {
    if(x <= 18.) return log1p(exp(x));
    if(x > 33.3) return x;

    return x + exp(-x);
}
