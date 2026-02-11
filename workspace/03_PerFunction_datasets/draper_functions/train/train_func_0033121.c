step(vector<double> &value, unsigned int nrow,
		    unsigned int ncol, double s, RNG *rng) const
{

    int r = pick(nrow, rng);


    int c1 = pick(ncol, rng);
    int c2 = pick(ncol - 1, rng);
    if (c2 >= c1) ++c2;


    double eps = rng->normal() * s;
    value[c1 * nrow + r] += eps;
    value[c2 * nrow + r] -= eps;
}
